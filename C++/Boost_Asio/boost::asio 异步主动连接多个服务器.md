## [boost::asio 异步主动连接多个服务器](http://blog.chinaunix.net/uid-24544542-id-187509.html)
ATC.hpp
```cpp
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
#include <set>
#include <map>
#include "Message.hpp"
#include "SQLite.hpp"

using boost::asio::deadline_timer;
using boost::asio::ip::tcp;
using boost::asio::ip::udp;

using namespace std;
using namespace PWRD;
using namespace PWRD::SQL;
using namespace PWRD::Protocol;

typedef map<string, int> Peers;
typedef map<string, int> Stats;
typedef map<string, string> Files;
typedef map<string, tcp::socket* > Sockets;
#define DEADLINE 10
#define MAXLEN 1024
#define SECONDS 5

namespace PWRD{
    namespace Network{
        class Session{
            public: 
                Session(boost::asio::ip::tcp::socket &_socket, boost::asio::io_service &io_service, const char *path);
                ~Session();
                void start();

                void stop();
                void delivery(string &ip);

            private:
                void handle_connect(const boost::system::error_code& ec,
                        tcp::resolver::iterator endpoint_iter);

                void start_read();

                void handle_read_header(const boost::system::error_code& ec);

                void start_delivery();

                void handle_read_body(const boost::system::error_code& ec);

                void start_write_heartbeat();

                void handle_write_heartbeat(const boost::system::error_code& ec);
                void handle_wait(const boost::system::error_code& ec);
                void handle_write_config(const boost::system::error_code& ec, Configure &conf);

            private:
                bool stopped_;
                tcp::socket &socket_;
                Header header_;
                HeartbeatMessage heartbeat_message_;
                DataMessage packet_message_;
                ConfigMessage conf_message_;
                deadline_timer heartbeat_timer_;
                Callback *callback_;
                char *input_stream_;

        };

        class SessionPool{
            public:
                SessionPool();
                ~SessionPool();
                void join(string&, Session *);
                void delivery(string&);
                void leave(string &ip);

            private:
                std::map<string, Session *> session_pool_;    
        };
        /************************************************************
         * Usage: Client will connect to every server and it's never
         *     stopped until you shutdown it. Connect action will 
         *    start in every DEADLINE seconds
         ************************************************************/
        class Client{
            public:
                void stop();
                void start();
                Client(boost::asio::io_service &_io_service, boost::asio::io_service &_io_service_data, const char *_sqlite);
            protected:
                void handle_wait_update();
                void handle_update();
                void start_connect();
                void handle_connect(const boost::system::error_code& ec,Peers::iterator it);
                void handle_deadline();
                void check_all();
            private:

                Peers peers_;
                Sockets sockets_;
                Stats status_;
                Files files_;

                deadline_timer deadline_;
                boost::asio::io_service &io_service_;
                const char * sqlite_;
                bool all_;

                SessionPool session_pool_;

                boost::asio::io_service &io_service_data_;

        };
    };
};
```

ATC.cpp
```cpp
#include "ATC.hpp"
namespace PWRD{
    namespace Network{
        //-------------------------------------------------------------------------

        //Session

        //-------------------------------------------------------------------------

        Session::Session(boost::asio::ip::tcp::socket &_socket, boost::asio::io_service &io_service, const char *path)
            :socket_(_socket),
            heartbeat_timer_(io_service),
            stopped_(false)
        {
            callback_ = new Callback(path);
            input_stream_ = new char[MAXLEN];
        }

        Session::~Session(){
            delete callback_;
            delete input_stream_;    
        }
        void Session::start(){
            start_read();
            start_write_heartbeat();
        }

        void Session::stop(){
            stopped_ = true;
            socket_.close();
            heartbeat_timer_.cancel();
        }

        void Session::start_read(){
            socket_.async_receive( 
                    boost::asio::buffer(&header_, HEADERLEN),
                    boost::bind(&Session::handle_read_header, this, 
                        boost::asio::placeholders::error)
                    );
        }

        void Session::handle_read_header(const boost::system::error_code& ec){
            if(stopped_)
                return;    
            if(!ec){
                if(HEARTBEAT == header_.type){
                    logs.write_log(NORMAL, "info:Receive heartbeat message");    
                    //heartbeat_timer_.expires_from_now(boost::posix_time::seconds(SECONDS));

                    start_read();
                }    
                else if(PACKET == header_.type){
                    socket_.async_receive(
                            boost::asio::buffer(input_stream_, header_.length),
                            boost::bind(&Session::handle_read_body, this, 
                                boost::asio::placeholders::error)
                            );
                    logs.write_log(NORMAL, "info:Receive Packet message: %d bytes", header_.length);    
                }
            }
            else{
                logs.write_log(NORMAL, "Error on receive: %s", (ec.message()).c_str());    
                stop();
            }
        }

        void Session::handle_read_body(const boost::system::error_code& ec){
            if(stopped_)
                return;    
            if(!ec){
                if(packet_message_.Parse(input_stream_, header_.length)){
                    Packet * packet = packet_message_.pack();
                    logs.write_log(NORMAL, "info:Receive data: %s", (packet->data()).c_str());
                    callback_->Write(packet);            
                }

                start_read();
            }
            else{
                logs.write_log(NORMAL, "Error on receive: %s", (ec.message()).c_str());    
                stop();
            }
        }
        void Session::start_write_heartbeat(){
            if(stopped_)
                return ;    
            Header header;
            header.length = 0;
            header.type = HEARTBEAT;
            boost::asio::async_write(socket_, boost::asio::buffer(&header, HEADERLEN),
                    boost::bind(&Session::handle_write_heartbeat, this,
                        boost::asio::placeholders::error    ));
            logs.write_log(NORMAL, "info:Send heartbeat message--->");
        }
        void Session::handle_write_heartbeat(const boost::system::error_code& ec){
            if(stopped_)
                return ;    

            if(!ec){
                heartbeat_timer_.expires_from_now(boost::posix_time::seconds(SECONDS));
                heartbeat_timer_.async_wait(boost::bind(&Session::start_write_heartbeat, this));

            }
            else{
                logs.write_log(NORMAL, "info:Error on heartbeat: %s ", (ec.message()).c_str());
                stop();

            }
        }
        void Session::start_delivery(){
            if(stopped_)
                return ;    
            /* *
             * SQLite append
             * */
            Configure conf;
            conf_message_.set_conf(conf);
            conf_message_.Serialize();
            header_.length = conf_message_.length();
            header_.type = CONFIG;
            socket_.async_send(
                    boost::asio::buffer(&header_,    HEADERLEN),
                    boost::bind(&Session::handle_write_config, this, _1, conf)
                    //boost::asio::placeholders::error, conf)

                );
        }

        void Session::delivery(string &ip){
            if(stopped_)
                return ;    
            /* *
             * SQLite append
             * */
            Configure conf;
            conf_message_.set_conf(conf);
            conf_message_.Serialize();
            header_.length = conf_message_.length();
            header_.type = CONFIG;
            socket_.async_send(
                    boost::asio::buffer(&header_,    HEADERLEN),
                    boost::bind(&Session::handle_write_config, this, _1, conf)
                    //boost::asio::placeholders::error, conf)

                );
        }

        void Session::handle_write_config(const boost::system::error_code& ec, Configure &conf){
            if(stopped_)
                return ;    

            if(!ec){
                socket_.async_send(
                        boost::asio::buffer(conf_message_.data(), 
                            conf_message_.length()), 
                        boost::bind(&Session::handle_wait, this, _1)

                        );
            }
        }

        void Session::handle_wait(const boost::system::error_code &ec){
            return;    
        }
        
        //-------------------------------------------------------------------------

        //SessionPool

        //-------------------------------------------------------------------------

        SessionPool::SessionPool(){
        }

        SessionPool::~SessionPool(){
        
        }

        void SessionPool::join(string &ip, Session *sess){
            session_pool_[ip] = sess;    
        }

        void SessionPool::delivery(string &ip){
            session_pool_[ip]->delivery(ip);    
        }

        void SessionPool::leave(string &ip){
            if(NULL == session_pool_[ip]){
                delete session_pool_[ip];    
            }
            session_pool_[ip] = NULL;    
        }

        //-------------------------------------------------------------------------

        //Client

        //-------------------------------------------------------------------------

        Client::Client(boost::asio::io_service &_io_service, boost::asio::io_service &_io_service_data, const char *_sqlite)
            :io_service_(_io_service),
            io_service_data_(_io_service_data),
            deadline_(_io_service),
            sqlite_(_sqlite), all_(false){

            }
        void Client::start()
        {
            //IP Table

            if(NULL == sqlite_){
                logs.write_log(NORMAL, "Sqlite dbname is invalid");
                return;
            }    
            SQLite::get_instance(sqlite_);
            AddrMap &map_ = SQLite::lookup();
            logs.write_log(NORMAL, "Get %d records", map_.size());
            AddrMap::iterator iter = map_.begin();
            for(; iter != map_.end(); iter++){
                Vector vect = iter->second;        
                string ip = vect[1], port = vect[2];
                status_[ip] = -1;
                peers_[ip] = std::atoi(port.c_str());
                sockets_[ip] = new boost::asio::ip::tcp::socket(io_service_);
                files_[ip] = "/tmp/file";
                //times_[ip] = boost::asio::deadline_timer(io_service_);

            }

            //start to connect

            start_connect();
            deadline_.async_wait(boost::bind(&Client::handle_deadline, this));

        }
        void Client::stop(){
            deadline_.cancel();
        }

        void Client::handle_wait_update(){

        }
        void Client::handle_update(){

        }
        void Client::start_connect(){
            if(peers_.size() > 0){
                deadline_.expires_from_now(boost::posix_time::seconds(DEADLINE));
                for(Peers::iterator it = peers_.begin();
                        it != peers_.end(); it++){

                    if( status_[it->first] < 0){
                        logs.write_log(NORMAL, "Start to connect: %s:%d", (it->first).c_str(), it->second);    

                        sockets_[it->first]->async_connect(
                                boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(it->first), it->second), 
                                boost::bind(&Client::handle_connect, 
                                    this, _1, it));

                    }
                }
            }
            else{
                stop();
            }

        }


        void Client::handle_connect(const boost::system::error_code& ec,
                Peers::iterator it){
            if(!sockets_[it->first]->is_open()){
                logs.write_log(NORMAL, "Connect time out");    
                return;
            }
            else if(ec){
                logs.write_log(NORMAL, "Connect error:%s", (ec.message()).c_str());
                //sockets_[it->first]->close();

                return;
            }
            else{
                logs.write_log(NORMAL, "Connect ok! it was conected with %s:%d", (it->first).c_str(), it->second);    
                status_[it->first] = 1;
                Session * ss = new Session(*(sockets_[it->first]), io_service_data_, (files_[it->first]).c_str());
                session_pool_.join(it->first, ss);
                ss->start();
            }
        }

        void Client::handle_deadline(){

            check_all();
            if(!all_){
                logs.write_log(NORMAL, "Timers out, begin to connect other server");
                start_connect();    
            }
            deadline_.expires_from_now(boost::posix_time::seconds(DEADLINE));
            deadline_.async_wait(boost::bind(&Client::handle_deadline, this));
        }

        void Client::check_all(){
            for(Stats::iterator it = status_.begin(); it != status_.end(); it++){
                if(it->second < 0){
                    all_ = false;
                    return;    
                }    
            }    
            all_ = true;
            return;

        }

    };
};
```
