
<%@ page contentType="text/html;charset=UTF-8" language="java" %>


<head>
    <script src="<%=request.getContextPath()%>/script/jquery.js"></script>
    <link rel="stylesheet" type="text/css" href="<%=request.getContextPath()%>/themes/default/easyui.css">
    <link rel="stylesheet" type="text/css" href="<%=request.getContextPath()%>/themes/icon.css">
    <script type="text/javascript" src="<%=request.getContextPath()%>/script/jquery.min.js"></script>
    <script type="text/javascript" src="<%=request.getContextPath()%>/script/jquery.easyui.min.js"></script>
    <script type="text/javascript" src="<%=request.getContextPath()%>/script/datagrid-detailview.js"></script>
</head>

<table id="most-useful-user" title="users" class="easyui-datagrid" style="width:1200px;height:500px;"
       rownumbers="true" fitColumns="true" singleSelect="true">
    <thead>
    <tr>
        <th field="uid" width="12" >uid</th>
        <th field="login" width="12">login</th>
        <th field="uname" width="12">uname</th>
        <th field="address" width="12">address</th>
        <th field="phoneno" width="12">Phone No.</th>
        <th field="average" width="12">Usefulness score</th>
    </tr>
    </thead>
</table>


<a class="easyui-linkbutton" iconCls="icon-ok" href="<%=request.getContextPath()%>/index.jsp">Return</a>

<script>
    $('#most-useful-user').datagrid({
        url: '<%=request.getContextPath()%>/UserAction/getMostUsefulUser.jsp',
        fitColumns: true
    });
</script>
