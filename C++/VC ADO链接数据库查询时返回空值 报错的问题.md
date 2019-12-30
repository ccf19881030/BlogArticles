## [VC ADO链接数据库查询时返回空值 报错的问题](http://blog.sina.com.cn/s/blog_62b3b4790102v5l6.html)
```cpp
while(m_AdoConn.m_pRecordset->adoEOF==0)
{
m_grid.InsertItem(0,"");
        m_grid.SetItemText(0,0,(char*)(_bstr_t)m_pRecordset->GetCollect("学号"));
m_grid.SetItemText(0,1,(char*)(_bstr_t)m_pRecordset->GetCollect("姓名"));
m_grid.SetItemText(0,2,(char*)(_bstr_t)m_pRecordset->GetCollect("性别"));
m_grid.SetItemText(0,3,(char*)(_bstr_t)m_pRecordset->GetCollect("民族"));
m_grid.SetItemText(0,4,(char*)(_bstr_t)m_pRecordset->GetCollect("政治面貌"));
m_grid.SetItemText(0,5,(char*)(_bstr_t)m_pRecordset->GetCollect("宿舍"));
m_grid.SetItemText(0,6,(char*)(_bstr_t)m_pRecordset->GetCollect("电话"));
m_grid.SetItemText(0,7,(char*)(_bstr_t)m_pRecordset->GetCollect("QQ"));

//判断备注是否为空
_variant_t var;
var = m_pRecordset->GetCollect("备注"); 
if(var.vt != VT_NULL)
    m_grid.SetItemText(0,8,(char*)(_bstr_t)m_pRecordset->GetCollect("备注"));
```
终于找到解决办法
