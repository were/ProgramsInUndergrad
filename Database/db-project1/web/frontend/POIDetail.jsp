<%@ page import="acmdb.BrowsingPOI" %><%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/10
  Time: 上午2:31
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    if (session.getAttribute("login") == null) {
        out.println("Please login first!");
        return ;
    }
    if ("admin".equals(session.getAttribute("login"))) {
        out.println("Admin can only manage");
        return ;
    }
%>

<div class="easyui-dialog" closed="true" id="form-visit-<%=request.getParameter("pid")%>">
    <div class="ftitle">Visit POI</div>
    <form method="post" id="real-<%=request.getParameter("pid")%>">
        <div class="fitem">
            <label>How much did you spent?</label>
            <input class="easyui-validatebox textbox" data-options="required: true,validType:'number[1,100000]'" name="cost" id="cost-<%=request.getParameter("pid")%>"/>
        </div>
        <div class="fitem">
            <label>How many people did you go with?</label>
            <input class="easyui-validatebox textbox" required="true" validType="number[1,100]" name="cnt" id="cnt-<%=request.getParameter("pid")%>"/>
        </div>
    </form>

    <a class="easyui-linkbutton" plain="true" id="done-<%=request.getParameter("pid")%>" href="#">Done</a>
    <%--<input type="button" id="done-<%=request.getParameter("pid")%>" value="Done"/>--%>
</div>

<div class="easyui-dialog" closed="true" id="form-confirm-<%=request.getParameter("pid")%>" style="width: 330px; height: 120px;">
    <div class="ftitle">Confirm</div>
    <div id="content-<%=request.getParameter("pid")%>" style="padding: 5px;"> </div>
    <a class="easyui-linkbutton" onclick="javascript:$('#dlg').dialog('close')" id="confirm-<%=request.getParameter("pid")%>" plain="true">Confirm</a>
</div>

<ul>
    <li>Average Score: <%=request.getParameter("avg")%></li>
    <li>Average Trusted Score: <%=request.getParameter("trust")%></li>
    <li id="keyword-<%=request.getParameter("pid")%>"></li>
</ul>

<%@include file="../widget/like-button.jsp"%>

<a class="easyui-linkbutton" id="call-form-<%=request.getParameter("pid")%>" iconCls="icon-add" plain="true">Visit Here!</a>

<%@include file="../widget/feedback-form.jsp"%>

<a href="<%=request.getContextPath()%>/frontend/comment.jsp?pid=<%=request.getParameter("pid")%>" class="easyui-linkbutton" id="show-comment-<%=request.getParameter("pid")%>" iconCls="icon-add" plain="true" onclick="javascript:$('#comment-<%=request.getParameter("pid")%>').dialog('open')">Show Feedback</a>

<%@include file="../widget/showSuggestion.jsp"%>

<script>
    $(document).ready(function () {
        $('#call-form-<%=request.getParameter("pid")%>').click(function () {
            $('#form-visit-<%=request.getParameter("pid")%>').dialog('open');
            $('#real-<%=request.getParameter("pid")%>').form('clear');
        });
        $('#like-<%=request.getParameter("pid")%>').click(function () {
            $.post(
                    '<%=request.getContextPath()%>/UserAction/announceLike.jsp',
                    {pid: <%=request.getParameter("pid")%>},
                    function (data) {
                        $('#like-<%=request.getParameter("pid")%>').linkbutton('disable');
                    }
            );
        });
        $('#done-<%=request.getParameter("pid")%>').click(function () {
            if ($('#form-visit-<%=request.getParameter("pid")%>').form('validate')) {
                $('#form-visit-<%=request.getParameter("pid")%>').dialog('close');
                $('#form-confirm-<%=request.getParameter("pid")%>').dialog('open');
                $('#content-<%=request.getParameter("pid")%>').text("Are you sure that you went with " + $("#cnt-<%=request.getParameter("pid")%>").val() + " person(s) and spent $" + $('#cost-<%=request.getParameter("pid")%>').val() + "?");
            }
        });
        $('#confirm-<%=request.getParameter("pid")%>').click(function () {
            $.post(
                    '<%=request.getContextPath()%>/UserAction/visitPOI.jsp',
                    {
                        pid: <%=request.getParameter("pid")%>,
                        cost: $('#cost-<%=request.getParameter("pid")%>').val(),
                        cnt: $("#cnt-<%=request.getParameter("pid")%>").val()
                    },
                    function (data) {
                        alert(data);
                        $('#form-confirm-<%=request.getParameter("pid")%>').dialog('close');
                        $('#suggestion-dialog').dialog('open');
                        makeGrid(<%=request.getParameter("pid")%>);
                    }
            );
        });
        $.post('<%=request.getContextPath()%>/POIAction/getKeyword.jsp',
                {pid: <%=request.getParameter("pid")%>},
                function (data) {
                    data = eval(data);
                    var keywords = "";
                    for (var i = 0; i < data.length; ++i) {
                        if (i + 1 < data.length) {
                            keywords += data[i].text + ", ";
                        } else {
                            keywords += data[i].text;
                        }
                    }
                    //alert(keywords);
                    if (keywords.length != 0)
                        $('#keyword-<%=request.getParameter("pid")%>').text("Keywords: " + keywords);
                    else
                        $('#keyword-<%=request.getParameter("pid")%>').text("No keyword!");
                }
        );
    });
    $.extend($.fn.validatebox.defaults.rules, {
        number: {
            validator: function(value,param){
                return !isNaN(value) && Number(value) >= param[0] && Number(value) <= param[1];
            },
            message: 'Input must be a number in range {0}~{1}!'
        }
    });

</script>
