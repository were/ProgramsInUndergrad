<%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/11
  Time: 上午2:37
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<div class="easyui-dialog" closed="true" id="suggestion-dialog">
    <div>People go to this place also went to the following (click to show feedbacks):</div>
    <table id="suggestion" title="Suggestion" class="easyui-datagrid" style="width:350px;height:350px;"
           rownumbers="true" fitColumns="true" singleSelect="true" >
        <thead>
        <tr>
            <th field="pname" width="12" >POI name</th>
            <th field="address" width="12">Address</th>
            <th field="cnt" width="12">People went</th>
        </tr>
        </thead>
    </table>
</div>

<script>
    function makeGrid(pid) {
        $('#suggestion').datagrid({
            url: "<%=request.getContextPath()%>/POIAction/suggestion.jsp?pid="+pid,
            onSelect: function (index, row) {
                window.location = "<%=request.getContextPath()%>/frontend/comment.jsp?pid="+row.pid;
            }
        });
    }
</script>