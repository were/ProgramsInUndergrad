<%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/8
  Time: 上午2:00
  To change this template use File | Settings | File Templates.
--%>

<div class="easyui-dialog" id="edit-<%=request.getParameter("pid")%>" buttons="#edit-buttons-<%=request.getParameter("pid")%>" closed="true">
    <ul id="key-list-<%=request.getParameter("pid")%>" class="easyui-datalist" url="<%=request.getContextPath()%>/POIAction/getKeyword.jsp?pid=<%=request.getParameter("pid")%>" style="width: 100px; padding: 5px;">

    </ul>
    <a href="#" class="easyui-linkbutton" iconCls="icon-cancel" plain="true" onclick="deleteKeyword()">Delete selected</a> <br>
    New keyword: <input class="easyui-validatebox" required="true" id="new-keyword-<%=request.getParameter("pid")%>" onkeypress="addKeyword()"/>
</div>

<form method="post">
    <table class="dv-table" style="width:100%;background:#fafafa;padding:5px;margin-top:5px;">
        <tr>
            <input name="pid" value="<%=request.getParameter("pid")%>" style="display:none;"/>
            <td>POI Name</td>
            <td><input name="pname" class="easyui-validatebox" required="true"/></td>
            <td>Address</td>
            <td><input name="address" class="easyui-validatebox" required="true"/></td>
            <td>Phone No.</td>
            <td><input name="phoneno" class="easyui-validatebox" required="true"/></td>
            <td>Year</td>
            <td><input name="year" class="easyui-validatebox" required="true"/></td>
        </tr>
        <tr>
            <td>Category</td>
            <td><input name="category" class="easyui-validatebox" required="true"/></td>
            <td>URL</td>
            <td><input name="url" class="easyui-validatebox" required="true"/></td>
            <td>Operation</td>
            <td><input name="operation" class="easyui-validatebox" required="true"/></td>
            <td>Price</td>
            <td><input name="price" class="easyui-validatebox" required="true"/></td>
        </tr>
    </table>
    <div style="padding:5px 0;text-align:right;padding-right:30px">
        <a href="#" class="easyui-linkbutton" iconCls="icon-edit" plain="true" onclick="editKeywords(<%=request.getParameter("index")%>)">Edit keywords</a>
        <a href="#" class="easyui-linkbutton" iconCls="icon-save" plain="true" onclick="saveItem(<%=request.getParameter("index")%>)">Save</a>
        <a href="#" class="easyui-linkbutton" iconCls="icon-cancel" plain="true" onclick="cancelItem(<%=request.getParameter("index")%>)">Cancel</a>
    </div>
</form>
<script>
    function saveItem(index) {
        //var row = $('#dg').datagrid('getRows')[index];
        $('#dg').datagrid('getRowDetail',index).find('form').form('submit',{
            url: '<%=request.getContextPath()%>/POIAction/updatePOI.jsp',
            onSubmit: function(){
                return $(this).form('validate');
            },
            success: function(data){
                //data = eval('('+data+')');
                alert(data);
                data.isNewRecord = false;
                $('#dg').datagrid('collapseRow',index);
                $('#dg').datagrid('updateRow',{
                    index: index,
                    row: data
                });
                $('#dg').datagrid('reload');
            }
        });
    }
    function cancelItem(index){
        var row = $('#dg').datagrid('getRows')[index];
        if (row.isNewRecord){
            $('#dg').datagrid('deleteRow',index);
        } else {
            $('#dg').datagrid('collapseRow',index);
        }
    }
    function editKeywords(pid) {
        $('#edit-<%=request.getParameter("pid")%>').dialog('open');
    }
    function addKeyword() {
        if (event.keyCode == "13"){
            var input = $('#new-keyword-<%=request.getParameter("pid")%>');
            $.post(
                    '<%=request.getContextPath()%>/POIAction/addKeyword.jsp',
                    {pid: <%=request.getParameter("pid")%>, keyword: input.val()},
                    function (data) {
                        $('#key-list-<%=request.getParameter("pid")%>').datalist('reload');
                    }
            );
            input.val("");
        }
    }
    function deleteKeyword() {
        key = $('#key-list-<%=request.getParameter("pid")%>').datalist('getSelected');
        $.post(
                '<%=request.getContextPath()%>/POIAction/eraseKeyword.jsp',
                {pid: <%=request.getParameter("pid")%>, keyword: key.text},
                function (data) {
                    $('#key-list-<%=request.getParameter("pid")%>').datalist('reload');
                }
        );
    }
</script>