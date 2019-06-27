## [使用boost.filesystem检查文件是否存在的正确方式](http://zplutor.github.io/2018/04/09/proper-way-to-check-file-existence-using-boost-filesystem/)
在我参与的项目中，使用了boost.filesystem进行文件操作。boost.filesystem在发生错误的时候会抛出异常，但是在大部分情况下这些异常是可以忽略的，例如，在检查文件是否存在的时候，发生错误可以等同于文件不存在。虽然boost.filesystem也提供了重载函数，通过输出参数返回错误来代替异常，但是在每个调用点都得定义一个输出参数，稍显麻烦。所以，为了简化客户代码，我们实现了一些包装函数，如下所示：
```cpp
bool IsFileExistent(const boost::filesystem::path& path) {
    boost::system:error_code error;
    return boost::filesystem::is_regular_file(path, error);
}
```
上面的函数用来检查文件是否存在，使用了boost::filesystem::is_regular_file。当path指向一个“常规文件”的时候，认为该文件存在；否则其它任何情况都认为文件不存在。

这个函数一直都很正常，直到最近有用户反馈，当发送OneDrive同步文件夹中的文件时，会出现文件不存在的提示，而这个文件明明是存在的。经过排查，我发现当OneDrive开启了“按需文件”功能时，boost::filesystem::is_regular_file对于同步文件夹中的文件会返回false。这个功能的设置界面如下图所示：
当开启了“按需文件”功能时，OneDrive中的文件信息会同步到本地文件系统中，但文件内容不会立即同步，只有真正用到文件内容时才会同步下来。这样一来可以节省本地的硬盘空间。并不是所有Windows系统都支持该功能，只有安装了2017年10月份发布的秋季更新的Windows 10系统才可以。

显然，当OneDrive中的文件还没有将内容同步下来时，它并不算是一个“常规文件”，难怪boost::filesystem::is_regular_file会返回false。事实上，用boost::filesystem::status获取这些文件的类型时，会返回symlink_file，boost.filesystem将它们视为符号链接文件。

不论是常规文件还是符号链接文件，呈现给用户的都是能够正常使用的文件。所以，不能单纯地用boost::filesystem::is_regular_file来检查文件是否存在了，下面是包装函数的改进版本：
```cpp
bool IsFileExistent(const boost::filesystem::path& path) {

    boost::system:error_code error;
    auto file_status = boost::filesystem::status(path, error);
    if (error) {
        return false;
    }

    if (! boost::filesystem::exists(file_status)) {
        return false;
    }

    if (boost::filesystem::is_directory(file_status)) {
        return false;
    }

    return true;
}
```
首先，通过boost::filesystem::status获取文件的信息，如果发生错误，则认为文件不存在。然后，使用boost::filesystem::exists判断文件是否存在，该函数不区分文件夹和文件，所以最后还要使用boost::filesystem::is_directory判断一下是否文件夹，只要不是文件夹，都认为文件是存在的。
