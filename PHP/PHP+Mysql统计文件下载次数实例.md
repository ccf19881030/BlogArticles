## [PHP+Mysql统计文件下载次数实例](http://blog.chinaunix.net/uid-31508513-id-5826198.html)
PHP+Mysql统计文件下载次数实例，实现的原理也很简单，是通过前台点击链接download.php传参id，来更新点击次数。
* 获取文件列表：
```php
<?php
require 'conn.php';
 
$query = mysql_query("SELECT * FROM downloads");
$lists = array();
while ($row = mysql_fetch_assoc($query)) {
    $lists[] = $row;
}
?>
```

* 读取文件列表，并加上download.php链接和参数id：
```php
<ul class="filelist">
    <?php foreach ($lists as $v) { ?>
        <li><a href="download.php?id="><?php echo $v['filename'] ?><span class="downcount" title="下载次数"><?php echo $v['downloads'] ?></span><span class="download">点击下载</span></a></li>
                <?php } ?>
</ul>
```
* 点击下载按钮，累加文件次数：
```php
$(function() {
        $('ul.filelist a').live('click', function() {
            var count = $('.downcount', this);
            count.text(parseInt(count.text()) + 1);
        });
});
```

* download.php文件源码：
```php
<?php
$id = (int) $_GET['id'];
 
if (!isset($id) || $id == 0)
    die('参数错误!');
$query = mysql_query("select * from downloads where id='$id'");
$row = mysql_fetch_array($query);
if (!$row)
    exit;
$filename = iconv('UTF-8', 'GBK', $row['filename']); //中文名称注意转换编码
$savename = $row['savename']; //实际在服务器上的保存名称
$myfile = 'files/' . $savename; //文件
 
if (file_exists($myfile)) {
    mysql_query("update downloads set downloads=downloads+1 where id='$id'");
    $file = @ fopen($myfile, "r");
    header("Content-type: application/octet-stream");
    header("Content-Disposition: attachment; filename=" . $filename);
    while (!feof($file)) {
        echo fread($file, 50000);
    }
    fclose($file);
    exit;
} else {
    echo '文件不存在！';
}
?>
```
