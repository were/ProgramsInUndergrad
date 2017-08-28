<%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/10
  Time: 上午2:11
  To change this template use File | Settings | File Templates.
--%>

<head>
    <script src="<%=request.getContextPath()%>/script/jquery.js"></script>
    <link rel="stylesheet" type="text/css" href="<%=request.getContextPath()%>/themes/default/easyui.css">
    <link rel="stylesheet" type="text/css" href="<%=request.getContextPath()%>/themes/icon.css">
    <script type="text/javascript" src="<%=request.getContextPath()%>/script/jquery.min.js"></script>
    <script type="text/javascript" src="<%=request.getContextPath()%>/script/jquery.easyui.min.js"></script>
    <script type="text/javascript" src="<%=request.getContextPath()%>/script/datagrid-detailview.js"></script>
</head>

<%
    //out.println((String) session.getAttribute("login"));
    if ("admin".equals(session.getAttribute("login"))) {
        return ;
    }
%>

<h1>POIs</h1>
<table id="dg" title="POIs" class="easyui-datagrid" style="width:1200px;height:500px;"
       pagination="true" rownumbers="true" fitColumns="true" singleSelect="true" toolbar="#search-bar">
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
    </tr>
    </thead>
</table>

<div>
    <a class="easyui-linkbutton" href="<%=request.getContextPath()%>/frontend/popularPOI.jsp" plain="true">Most Popular POI</a>
    <a class="easyui-linkbutton" href="<%=request.getContextPath()%>/frontend/highRatedPOI.jsp" plain="true">Most High Rated POI</a>
    <a class="easyui-linkbutton" href="<%=request.getContextPath()%>/frontend/expensivePOI.jsp" plain="true">Most Expensive POI</a>
</div>

<div id="search-bar">
    <input id="ge" class="easyui-validatebox" data-options="validType:'number'" style="border:1px solid #ccc;width: 100px;" onchange="filterPOI()">
    <span>&le; Price &le;:</span>
    <input id="le" class="easyui-validatebox" data-options="validType:'number'" style="border:1px solid #ccc;width: 100px;" onchange="filterPOI()">
    <span>Address:</span>
    <input id="address" style="border:1px solid #ccc;" onchange="filterPOI()">
    <span>Keyword:</span>
    <input id="keyword" style="border:1px solid #ccc;" onchange="filterPOI()">
    <span>Category:</span>
    <input id="category" style="border:1px solid #ccc;" onchange="filterPOI()">
    <span>Sort by:</span>
    <select id="order" onchange="filterPOI()">
        <option value="">None</option>
        <option value="priceAsc">Ascending Price</option>
        <option value="priceDesc">Descending Price</option>
        <option value="bestFeedback">Best Feedback</option>
        <option value="trustFeedback">Trusted Feedback</option>
    </select>
</div>

<script>
    $(function() {
        $("#dg").datagrid({
            view: detailview,
            detailFormatter: function () {
                return '<div class="ddv"></div>';
            },
            url: "<%=request.getContextPath()%>/POIAction/filterPOI.jsp",
            fitColumns: true,
            onExpandRow: function(index,row){
                var ddv = $(this).datagrid('getRowDetail',index).find('div.ddv');
                ddv.panel({
                    border:false,
                    cache:true,
                    href:'<%=request.getContextPath()%>/frontend/POIDetail.jsp?index='+index+'&pid='+row.pid+'&avg='+row.avg+'&trust='+row.trust,
                    onLoad:function(){
                        $('#dg').datagrid('fixDetailRowHeight', index);
                        $('#dg').datagrid('selectRow', index);
                        //$('#dg').datagrid('getRowDetail', index).find('form').form('load',row);
                    }
                });
                $('#dg').datagrid('fixDetailRowHeight',index);
            }
        });
    });
    function filterPOI() {
        $('#dg').datagrid('load',
                {
                    le: $('#le').val(),
                    ge: $('#ge').val(),
                    address: $('#address').val(),
                    keyword: $('#keyword').val(),
                    category: $('#category').val(),
                    order: $('#order').val()
                }
        );
    }
</script>

