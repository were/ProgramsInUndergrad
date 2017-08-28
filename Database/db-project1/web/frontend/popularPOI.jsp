<%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/11
  Time: 下午3:29
  To change this template use File | Settings | File Templates.
--%>


<%@ page contentType="text/html;charset=UTF-8" language="java" %>


<head>
    <script src="<%=request.getContextPath()%>/script/jquery.js"></script>
    <link rel="stylesheet" type="text/css" href="<%=request.getContextPath()%>/themes/default/easyui.css">
    <link rel="stylesheet" type="text/css" href="<%=request.getContextPath()%>/themes/icon.css">
    <script type="text/javascript" src="<%=request.getContextPath()%>/script/jquery.min.js"></script>
    <script type="text/javascript" src="<%=request.getContextPath()%>/script/jquery.easyui.min.js"></script>
    <script type="text/javascript" src="<%=request.getContextPath()%>/script/datagrid-detailview.js"></script>
</head>

<table id="popular-dg-POI" title="POIs" class="easyui-datagrid" style="width:1200px;height:500px;"
       rownumbers="true" fitColumns="true" singleSelect="true">
    <thead>
    <tr>
        <th field="pname" width="12" > POI name</th>
        <th field="address" width="12">Address</th>
        <th field="phoneno" width="12">Phone No.</th>
        <th field="year" width="12">Year Estab.</th>
        <th field="category" width="12">Category</th>
        <th field="url" width="12">URL</th>
        <th field="operation" width="12">Operation</th>
        <th field="price" width="12">Price</th>
        <th field="cnt" width="12">total visits</th>
    </tr>
    </thead>
</table>


<a class="easyui-linkbutton" iconCls="icon-ok" href="<%=request.getContextPath()%>/index.jsp">Return</a>

<script>
    $('#popular-dg-POI').datagrid({
        view: detailview,
        url: "<%=request.getContextPath()%>/POIAction/getPopularPID.jsp",
        detailFormatter: function () {
            return '<div class="ddv"></div>';
        },
        fitColumns: true,
        onExpandRow: function(index,row){
            var ddv = $(this).datagrid('getRowDetail',index).find('div.ddv');
            ddv.panel({
                border:false,
                cache:true,
                href:'<%=request.getContextPath()%>/frontend/POIDetail.jsp?index='+index+'&pid='+row.pid+'&avg='+row.avg+'&trust='+row.trust,
                onLoad:function(){
                    $('#popular-dg-POI').datagrid('fixDetailRowHeight', index);
                    $('#popular-dg-POI').datagrid('selectRow', index);
                    //$('#dg').datagrid('getRowDetail', index).find('form').form('load',row);
                }
            });
            $('#popular-dg-POI').datagrid('fixDetailRowHeight',index);
        }
    });
</script>
