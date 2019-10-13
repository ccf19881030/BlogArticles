commons-io.jar：
可以看成是java.io的扩展，用来帮助进行IO功能开发．它包含三个主要的领域:Utilityclasses-提供一些静态方法来完成公共任务．Filters-提供文件过滤器的各种实现．Streams-提供实用的Stream，reader与writer实现．
commons-beanutils.jar：
提供对Java反射和自省API的包装，主要提供了对于 JavaBean进行各种操作。
commons-digester.jar:
它能方便地将XML文档所定义的元素转化为JAVA对象，其实它的用法有点象栈(当然内在的原理就是那个古老的东西,只是提供了更高一层的封装)。
commons-lang.jar:
它扩展了标准 java.langAPI，增加了字符串操作方法、基本数值方法、对象反射、创建和串行化以及System属性。它还包含一个可继承的enum类型、对多种嵌套的Exception类型的支持、对java.util.Date的增强以及用于构建方法的实用程序，例如自动生成 toString()的结果、自动实现hashCode()和equals()方法、数组操作、枚举、日期和时间的处理等等。
ArrayUtils–用于对数组的操作，如添加、查找、删除、子数组、倒序、元素类型转换等；
BitField–用于操作位元，提供了一些方便而安全的方法；
BooleanUtils–用于操作和转换boolean或者Boolean及相应的数组；
CharEncoding–包含了Java环境支持的字符编码，提供是否支持某种编码的判断；
CharRange–用于设定字符范围并做相应检查；
CharSet–用于设定一组字符作为范围并做相应检查；
CharSetUtils–用于操作CharSet；
CharUtils–用于操作char值和Character对象；
ClassUtils–用于对Java类的操作，不使用反射；
ObjectUtils–用于操作Java对象，提供null安全的访问和其他一些功能；
RandomStringUtils–用于生成随机的字符串；
SerializationUtils–用于处理对象序列化，提供比一般Java序列化更高级的处理能力；
StringEscapeUtils–用于正确处理转义字符，产生正确的Java、JavaScript、HTML、XML和SQL代码；
StringUtils–处理String的核心类，提供了相当多的功能；
SystemUtils–在java.lang.System基础上提供更方便的访问，如用户路径、Java版本、时区、操作系统等判断；
Validate–提供验证的操作，有点类似assert断言；
WordUtils–用于处理单词大小写、换行等。
commons-codec.jar：
包含一些通用的编码解码算法。包括一些语音编码器，Hex,Base64, 以及URLencoder。


commons-collections.jar：
提供一个类包来扩展和增加标准的JavaCollection框架。
Bag接口：适用于包含一个对象的多个拷贝的集合
Buffer接口：适用于具有顺序的集合类，例如FIFOs(先进先出)
BidiMap(双向映射)：可以通过值查找键，也可以通过键查找值
Map迭代器：提供了对映射的快速迭代
对类型检查进行了封装，确保特定类的实例可以被添加到集合中
对转换进行了封装，将集合中的对象转换成被加入时的类型
对集合进行组合，使多个集合看起来就像一个集合一样
有序映射和set，保持元素添加时的顺序，包括一个基于LRU的map
标识映射可以给予对象的==来比较对象，而不是基于equals方法
引用映射可以允许键and/or值可以有控制的进行回收
很多比较器的实现
很多迭代器的实现
从数组或者枚举到集合的适配器
用来测试或者创建典型set理论的集合属性，例如与、或、闭包
commons-dbutil.jar:
对传统操作数据库的类进行二次封装，可以把结果集转化成List
(1)org.apache.commons.dbutils
DbUtils : 提供如关闭连接、装载JDBC驱动程序等常规工作的工具类
QueryRunner: 该类简单化了SQL查询，它与ResultSetHandler组合在一起使用可以完成大部分的数据库操作，能够大大减少编码量。
QueryLoader: 属性文件加载器，主要用于加载属性文件中的SQL到内存中。
(2)org.apache.commons.dbutils.handlers
ArrayHandler：将ResultSet中第一行的数据转化成对象数组ArrayListHandler将ResultSet中所有的数据转化成List，List中存放的是Object[]
BeanHandler：将ResultSet中第一行的数据转化成类对象
BeanListHandler：将ResultSet中所有的数据转化成List，List中存放的是类对象
ColumnListHandler：将ResultSet中某一列的数据存成List，List中存放的是Object对象
KeyedHandler：将ResultSet中存成映射，key为某一列对应为Map。Map中存放的是数据
MapHandler：将ResultSet中第一行的数据存成Map映射
MapListHandler：将ResultSet中所有的数据存成List。List中存放的是Map
ScalarHandler：将ResultSet中一条记录的其中某一列的数据存成Object


java开发中主要用到的jar包总结
axis.jar:SOAP引擎包
jaxrpc.jar:Axis运行所需要的组件包
saaj.jar:创建到端点的点到点连接的方法、创建并处理SOAP消息和附件的方法，以及接收和处理SOAP错误的方法.  
wsdl4j-1.5.1.jar:Axis运行所需要的组件包
activation.jar:JAF框架的jar包
annotations-api.jar:使用注解所需jar
ant.jar:用于自动化调用程序完成项目的编译，打包，测试等
aopalliance-1.0.jar:支持spring AOP
asm-2.2.3.jar:ASM字节码库
asm-commons-2.2.3.jar:ASM字节码库
asm-util-2.2.3.jar:Java字节码操纵和分析框架
aspectjrt.jar:处理事务和AOP所需的包
aspectjweaver.jar:处理事务和AOP所需的包
axiom-api-1.2.7.jar:Axis 对象模型
axiom-impl-1.2.7.jar:Axis 对象模型


bcprov-jdk15-140.jar:基于java1.5 的加密算法实现
bfmclientmodel.jar:使用WebSphere所需jar包
bpcclientcore.jar:使用WebSphere所需jar包
bpe137650.jar:提供远程访问BPE容器的实现。 
bsh-2.0b4.jar:解决负载逻辑运算


c3p0-0.9.0.jar:开放源代码的JDBC连接池
cglib-nodep-2.1_3.jar:Spring中自动代理所需jar包
cobertura.jar:测量测试覆盖率
commons-beanutils-1.7.0.jar:动态的获取/设值Java Bean的属性
commons-chain-1.1.jar:实现责任链设计模式的Java 类库
commons-codec-1.3.jar:用来处理常用的编码方法的工具类包，例如DES、SHA1、MD5、Base64等等
commons-collections-3.1.jar:对标准java Collection的扩展
commons-collections.jar:对标准java Collection的扩展
commons-discovery-0.2.jar:用来发现、查找和实现可插入式接口，提供一些一般类实例化、单件的生命周期管理的常用方法.db2jcc.jarjava连接DB2所需jar
commons-digester-1.8.jar:用于处理struts-config.xml配置文件
commons-fileupload-1.1.1.jar:struts上传文件
commons-httpclient-3.1.jar:用来简化HTTP客户端与服务器端进行各种通信编程实现
commons-io-1.1.jar:针对java.io.InputStream和Reader进行了扩展
commons-lang-2.4.jar:对java.lang.*的扩展
commons-logging-1.1.1.jar:日志包
commons-pool-1.3.jar:实现对象池化框架
commons-validator-1.3.1.jar:用来把验证规则程序提取出来，以供重复使用


db2jcc_license_cu.jar:java:连接DB2所需jar
dom4j-1.6.1.jar:解析XML


ehcache-1.2.4.jar:hibernate的二级缓存如果用ehcache的时候需要此jar包
emf.jar:基于Eclipse的模型框架
ezmorph-1.0.6.jar:使用JSON所需的jar包


FastInfoset-1.2.2.jar:使用WebService所需的jar包
freemarker-2.3.8.jar:Strus2支持的一种表现层框架


geronimo-activation_1.1_spec-1.0.2.jar:Apache Geronimo所带jar包，
geronimo-annotation_1.0_spec-1.1.1.jar:Apache Geronimo所带jar包
geronimo-javamail_1.4_spec-1.3.jar:Apache Geronimo所带jar包
geronimo-jaxws_2.1_spec-1.0.jar:Apache Geronimo所带jar包
geronimo-jms_1.1_spec-1.1.1.jar:Apache Geronimo所带jar包
geronimo-servlet_2.5_spec-1.2.jar:Apache Geronimo所带jar包
geronimo-stax-api_1.0_spec-1.0.1.jar:Apache Geronimo所带jar包


hibernate3.jar:Hibernate3的核心jar包
htmclientmodel.jar:使用WebSphere所需jar包


jakarta-oro.jar:一套文本处理工具，提供per15.0兼容的表达式，AWK-like表达式，Glob表达式。
javassist.jar:Javassist 字节码解释器
jaxb-api-2.1.jar:使用WebService所需的jar包
jaxb-impl-2.1.7.jar:使用CXF所需jar包
jaxb-xjc-2.1.7.jar:使用CXF所需jar包
jaxen-1.1.1.jar:解析XML
jcifs-1.2.22.jar:实现单点登陆
jdom2-1.0.jar:解析XML
jdom-1.0.jar:解析XML
jettison-1.0.1.jar:使用CXF所需jar包
jetty-6.1.9.jar:Jetty Http服务器jar
jetty-util-6.1.9.jar:Jetty Http服务器jar
jra-1.0-alpha-4.jar:使用CXF所需jar包
js-1.6R7.jar:使用CXF所需jar包
json-lib-2.2.3-jdk13.jar:使用JSON所需的jar包
jsonplugin-0.25.jar:strus2的JSON插件
jsr311-api-0.8.jar:使用CXF所需jar包
jstl.jar:JSTL标签库
jta.jar:标准的 JAVA 事务处理接口
junit.jar:用于单元测试
jxl.jar:通过java操作excel表格的工具类库
ldap.jar:JNDI目录服务和LDAO服务器所需的jar
ldapbp.jar:JNDI目录服务和LDAO服务器所需的jar


log4j-1.2.15.jar:提供日志功能


mail.jar:java发送邮件jar包


neethi-2.0.4.jar:使用CXF所需jar包


odmg-3.0.jar:ODMG是一个ORM的规范，Hibernate实现了ODMG规范，这是一个核心的库
ognl-2.6.11.jar:struts2中OGNL语言
ojdbc14.jar:Oracle数据库驱动包
opensaml-1.1.jar:使用CXF所需jar包
oro-2.0.8.jar:Validator框架所需的jar包
oscache-2.1.jar:Java 对象的缓存工具


poi-3.1-FINAL-20080629.jar:操作exce所需jar包
poi-contrib-3.1-FINAL-20080629.jar:操作exce所需jar包
poi-ooxml-3.6-20091214.jar:提供对office的word、excel、visio及ppt的操作
poi-ooxml-schemas-3.6-20091214.jar:提供对office的word、excel、visio及ppt的操作
poi-scratchpad-3.1-FINAL-20080629.jar:提供对office的word、excel、visio及ppt的操作
processCommon.jarIBM WebSphere:运行所需jar
ProcessCommonLibrary.jarIBM WebSphere:运行所需jar
processIdentity.jarIBM WebSphere:运行所需jar
ProcessInformation.jar:进程监视软件包
proxool-0.9.1.jar:数据库连接池
proxool-cglib.jar:数据库连接池


quartz-1.6.0.jar:开源作业调度框架


saaj-api-1.3.jar:使用axis所需的jar
saaj-impl-1.3.2.jar:使用axis所需的jar
serializer-2.7.1.jar:XML序列化
slf4j-jdk14-1.5.6.jar:整合各种日志框架的工具
spring208.jar:spring核心框架
spring-ldap-1.2-RC1.jar:spring下LDAP
spring-mock.jar:spring的测试框架
standard.jar:使用JSTL标签库所需的jar
stax-api-1.0.1.jar:解析XML
struts2-core-2.0.14.jar:struts2核心jar
struts2-spring-plugin-2.0.6.jar:struts2整合Spring所需jar


taglibs-datetime.jar:Apache开源组织提供标签库，用于格式化日期。
taglibs-mailer.jar:用于发送邮件
taglibs-string.jar:Apache开源组织提供标签库，用于对String的操作。
task137650.jar:Portal技术在SOA系统集成应用中实现所需的jar


utility.jar:Apache开源组织提供标签库


velocity-1.5.jar:一个免费的开源模板框架


wsdl4j-1.6.2.jar:用来解析服务的WSDl文件
wss4j-1.5.4.jar:创建CXF所需jar
wstx-asl-3.2.6.jar:创建CXF所需jar


xbean-spring-2.8.jar:使用xfire所需jar
xerces-2.6.2.jar:XML解析器
xfire-all-1.2.6.jar:用于实现WebService
XmlSchema-1.1.jar:使用xfire所需jar
xwork-2.0.7.jar:WebWork核心jar
