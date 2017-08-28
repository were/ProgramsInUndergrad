<%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/6
  Time: 下午10:58
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
    if (!"admin".equals(session.getAttribute("login"))) {
        return ;
    }
    if ("poiInsertionFail".equals(request.getParameter("error"))) {
        out.println("POI insertion failed");
    }
%>

<div id="dlg" class="easyui-dialog" style="width:400px;height:500px;padding:10px 20px" closed="true" buttons="#dlg-buttons">
    <div class="ftitle">New POI</div>
    <form method="post" action="<%=request.getContextPath()%>/POIAction/updatePOI.jsp" id="fm">
        <div class="fitem">
            <label>Name</label>
            <input class="easyui-validatebox textbox" required="true" name="pname"/>
        </div>
        <div class="fitem">
            <label>Address</label>
            <input class="easyui-validatebox textbox" required="true" name="address"/>
        </div>
        <div class="fitem">
            <label>Phone no.</label>
            <input class="easyui-validatebox textbox" required="true" name="phoneno"/>
        </div>
        <div class="fitem">
            <label>Year</label>
            <input class="easyui-validatebox textbox" data-options="required:true,validType:'length[4,4]'" name="year"/>
        </div>
        <div class="fitem">
            <label>Category</label>
            <input class="easyui-validatebox textbox" data-options="required:true" type="text" name="category"/>
        </div>
        <div class="fitem">
            <label>Url</label>
            <input class="easyui-validatebox textbox" data-options="required:true,validType:'url'" name="url"/>
        </div>
        <div class="fitem">
            <label>Operation</label>
            <input class="easyui-validatebox textbox" data-options="required:true" name="operation"/>
        </div>
        <div class="fitem">
            <label>Price</label>
            <input class="easyui-validatebox textbox" data-options="required:true" name="price"/>
        </div>
    </form>
</div>
<div id="dlg-buttons">
    <a href="#" class="easyui-linkbutton" iconCls="icon-ok" onclick="saveUser()">Save</a>
    <a href="#" class="easyui-linkbutton" iconCls="icon-cancel" onclick="javascript:$('#dlg').dialog('close')">Cancel</a>
</div>

<h1>POIs</h1>
<table id="dg" title="POIs" class="easyui-datagrid" style="width:1000px;height:500px;"
       toolbar="#toolbar" pagination="true"
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
    </tr>
    </thead>
</table>
<div id="toolbar">
    <a href="#" class="easyui-linkbutton" iconCls="icon-add" plain="true" onclick="newPOI()">New POI</a>
</div>
<div>
    <a href="<%=request.getContextPath()%>/frontend/mostTrustedUser.jsp" class="easyui-linkbutton" iconCls="icon-add" plain="true">Most Trusted User</a>
    <a href="<%=request.getContextPath()%>/frontend/mostUsefulUser.jsp" class="easyui-linkbutton" iconCls="icon-add" plain="true">Most Useful User</a>
</div>
<script>
    $(function() {
        $("#dg").datagrid({
            view: detailview,
            detailFormatter: function () {
                return '<div class="ddv"></div>';
            },
            url: "<%=request.getContextPath()%>/POIAction/getPOI.jsp",
            fitColumns: true,
            onExpandRow: function(index,row){
                var ddv = $(this).datagrid('getRowDetail',index).find('div.ddv');
                ddv.panel({
                    border:false,
                    cache:true,
                    href:'<%=request.getContextPath()%>/frontend/editPOI.jsp?index='+index+'&'+'pid='+row.pid,
                    onLoad:function(){
                        $('#dg').datagrid('fixDetailRowHeight', index);
                        $('#dg').datagrid('selectRow', index);
                        $('#dg').datagrid('getRowDetail', index).find('form').form('load',row);
                    }
                });
                $('#dg').datagrid('fixDetailRowHeight',index);
            }
        });
    });
    function newPOI() {
        $('#dlg').dialog('open');
        $('#fm').form('clear');
    }
    function saveUser() {
        $('#fm').form('submit', {
            url: "<%=request.getContextPath()%>/POIAction/updatePOI.jsp",
            onSubmit: function () {
                return $(this).form('validate');
            },
            success: function (result) {
                $('#dlg').dialog('close');
                $('#dg').datagrid('reload');
            }
        });
    }
    
</script>
