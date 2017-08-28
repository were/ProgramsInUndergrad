
<%@ page contentType="text/html;charset=UTF-8" language="java" %>


<head>
    <script src="<%=request.getContextPath()%>/script/jquery.js"></script>
    <link rel="stylesheet" type="text/css" href="<%=request.getContextPath()%>/themes/default/easyui.css">
    <link rel="stylesheet" type="text/css" href="<%=request.getContextPath()%>/themes/icon.css">
    <script type="text/javascript" src="<%=request.getContextPath()%>/script/jquery.min.js"></script>
    <script type="text/javascript" src="<%=request.getContextPath()%>/script/jquery.easyui.min.js"></script>
    <script type="text/javascript" src="<%=request.getContextPath()%>/script/datagrid-detailview.js"></script>
</head>

<table id="expensive-POI" title="POIs" class="easyui-datagrid" style="width:1200px;height:500px;"
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
        <th field="average" width="12">average cost</th>
    </tr>
    </thead>
</table>


<a class="easyui-linkbutton" iconCls="icon-ok" href="<%=request.getContextPath()%>/index.jsp">Return</a>

<script>
    $('#expensive-POI').datagrid({
        view: detailview,
        url: "<%=request.getContextPath()%>/POIAction/getExpensivePOI.jsp",
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
                    $('#expensive-POI').datagrid('fixDetailRowHeight', index);
                    $('#expensive-POI').datagrid('selectRow', index);
                }
            });
            $('#expensive-POI').datagrid('fixDetailRowHeight',index);
        }
    });
</script>
