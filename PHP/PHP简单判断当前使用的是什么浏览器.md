## [PHP简单判断当前使用的是什么浏览器](http://blog.chinaunix.net/uid-31508513-id-5826424.html)
### PHP简单判断当前使用的是什么浏览器，判断浏览器类型的方法，方便统计网站访问用户使用浏览器的比例。
```php
function userBrowser() {
    $user_OSagent = $_SERVER['HTTP_USER_AGENT'];
 
    if (strpos($user_OSagent, "Maxthon") && strpos($user_OSagent, "MSIE")) {
        $visitor_browser = "Maxthon(Microsoft IE)";
    } elseif (strpos($user_OSagent, "Maxthon 2.0")) {
        $visitor_browser = "Maxthon 2.0";
    } elseif (strpos($user_OSagent, "Maxthon")) {
        $visitor_browser = "Maxthon";
    } elseif (strpos($user_OSagent, "MSIE 9.0")) {
        $visitor_browser = "MSIE 9.0";
    } elseif (strpos($user_OSagent, "MSIE 8.0")) {
        $visitor_browser = "MSIE 8.0";
    } elseif (strpos($user_OSagent, "MSIE 7.0")) {
        $visitor_browser = "MSIE 7.0";
    } elseif (strpos($user_OSagent, "MSIE 6.0")) {
        $visitor_browser = "MSIE 6.0";
    } elseif (strpos($user_OSagent, "MSIE 5.5")) {
        $visitor_browser = "MSIE 5.5";
    } elseif (strpos($user_OSagent, "MSIE 5.0")) {
        $visitor_browser = "MSIE 5.0";
    } elseif (strpos($user_OSagent, "MSIE 4.01")) {
        $visitor_browser = "MSIE 4.01";
    } elseif (strpos($user_OSagent, "MSIE")) {
        $visitor_browser = "MSIE 较高版本";
    } elseif (strpos($user_OSagent, "NetCaptor")) {
        $visitor_browser = "NetCaptor";
    } elseif (strpos($user_OSagent, "Netscape")) {
        $visitor_browser = "Netscape";
    } elseif (strpos($user_OSagent, "Chrome")) {
        $visitor_browser = "Chrome";
    } elseif (strpos($user_OSagent, "Lynx")) {
        $visitor_browser = "Lynx";
    } elseif (strpos($user_OSagent, "Opera")) {
        $visitor_browser = "Opera";
    } elseif (strpos($user_OSagent, "Konqueror")) {
        $visitor_browser = "Konqueror";
    } elseif (strpos($user_OSagent, "Mozilla/5.0")) {
        $visitor_browser = "Mozilla";
    } elseif (strpos($user_OSagent, "Firefox")) {
        $visitor_browser = "Firefox";
    } elseif (strpos($user_OSagent, "U")) {
        $visitor_browser = "Firefox";
    } else {
        $visitor_browser = "其它";
    }
    return $visitor_browser;
}
```
### 直接调用 userBrowser()
```php
<?php echo "您现在使用的浏览器是：" . userBrowser();?>
```
