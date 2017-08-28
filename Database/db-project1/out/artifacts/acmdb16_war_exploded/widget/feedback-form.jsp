<%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/10
  Time: 下午2:35
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<a class="easyui-linkbutton" id="show-feedback-<%=request.getParameter("pid")%>" iconCls="icon-add" plain="true" onclick="javascript:$('#feedback-<%=request.getParameter("pid")%>').dialog('open')">Write Feedback</a>

<div id="feedback-<%=request.getParameter("pid")%>" class="easyui-dialog" style="width:400px;height:500px;padding:10px 20px" closed="true" buttons="#dlg-buttons">
    <div class="ftitle">Feedback of a POI</div>
    <form method="post" action="<%=request.getContextPath()%>/UserAction/feedback.jsp" id="feedback-fm-<%=request.getParameter("pid")%>">
        <input name="pid" value="<%=request.getParameter("pid")%>" style="display: none;"/>
        <div clas="fitem">
            <label>Score</label>
            <select name="score">
                <%  for (int i = 10; i >= 0; --i) {%>
                    <option value="<%=i%>"><%=i%></option>
                <%  }%>
            </select>
        </div>
        <div class="fitem">
            <label>Comment</label>
            <br>
            <input class="easyui-textbox" name="comment" style="width:250px; height: 250px;" multiline="true"/>
        </div>
        <a class="easyui-linkbutton" id="submit-feedback-<%=request.getParameter("pid")%>" iconCls="icon-save" plain="true">Submit</a>
    </form>
</div>

<script>
    $('#submit-feedback-<%=request.getParameter("pid")%>').click(function () {
        $('#feedback-fm-<%=request.getParameter("pid")%>').form('submit',{
            url: '<%=request.getContextPath()%>/UserAction/feedback.jsp',
            onSubmit: function () {
                return true;
            },
            success: function (data) {
                alert(data);
                $('#feedback-<%=request.getParameter("pid")%>').dialog('close');
            }
        });

    });
</script>
