<%@ page import="acmdb.User" %>
<%@ page import="acmdb.Connector" %>
<%@ page import="java.sql.ResultSet" %>
<%@ page import="acmdb.Distance" %><%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/10
  Time: 下午8:29
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<div>
    <%=request.getParameter("cmt").length() != 0 ? request.getParameter("cmt") : "This guy is lazy and says nothing..."%>
<%  if (((User) session.getAttribute("User")).uid != Integer.parseInt(request.getParameter("uid"))) { %>
<div>
    <%
        int dis = Distance.dis(((User) session.getAttribute("User")).uid, Integer.parseInt(request.getParameter("uid")));
        if (dis == -1) {%>
        <div>You have no favourite in common... </div>
    <%  } else {%>
        <div>You have <%=dis%>-degree with him...　</div>
    <%  }%>
    <div><h3>Is this guy trusted?</h3></div>
    <%
        Connector tmp1 = new Connector();
        ResultSet res = tmp1.stmt.executeQuery(String.format("SELECT * FROM Trust WHERE from_uid=%d AND to_uid=%s", ((User) session.getAttribute("User")).uid, request.getParameter("uid")));
        if (!res.next()) {%>
            <div id="trust-level-<%=request.getParameter("fid")%>">
                <a href="#" iconCls="icon-ok" class="easyui-linkbutton" plain="true" onclick="trust(<%=request.getParameter("uid")%>, 1)">Trust</a>
                <a href="#" iconCls="icon-cancel" class="easyui-linkbutton" plain="true" onclick="trust(<%=request.getParameter("uid")%>, -1)">NotTrust</a>
            </div>
    <%  } else {%>
            <div><%=res.getInt("trusted") == 1 ? "Trusted" : "NotTrusted"%></div>
    <%  }
        tmp1.closeStatement();
        tmp1.closeConnection();
    %>
    <div><h3>Is it useful?</h3></div>
    <%
        Connector tmp2 = new Connector();
        res = tmp2.stmt.executeQuery(String.format("SELECT * FROM Opinion WHERE uid=%d AND fid=%s", ((User) session.getAttribute("User")).uid, request.getParameter("fid")));
        if (!res.next()) {
    %>
    <div id="usage-level-<%=request.getParameter("fid")%>">
        <a href="#" class="easyui-linkbutton" plain="true" onclick="rate(<%=request.getParameter("fid")%>, 2)">Very Useful</a>
        <a href="#" class="easyui-linkbutton" plain="true" onclick="rate(<%=request.getParameter("fid")%>, 1)">Useful</a>
        <a href="#" class="easyui-linkbutton" plain="true" onclick="rate(<%=request.getParameter("fid")%>, 0)">Useless</a>
    </div>
    <%  } else {%>
        <div><%=res.getInt("score") == 0 ? "Useless" : res.getInt("score") == 1 ? "Usefull" : "Very useful"%></div>
    <%  }
        tmp2.closeStatement();
        tmp2.closeConnection();
    %>
</div>
<%  } else {%>
<div>
    No one can rate/trust their own/temself.
</div>
</div>
<%  }%>
<script>
    function trust(uid, trusted) {
        $.post(
                '<%=request.getContextPath()%>/UserAction/trust.jsp',
                {uid: uid, trusted: trusted},
                function (data) {
                    alert(data);
                    location.reload(true);
                    <%--if (trusted == 1)--%>
                        <%--$('#trust-level-<%=request.getParameter("fid")%>').text('Trusted');--%>
                    <%--else--%>
                        <%--$('#trust-level-<%=request.getParameter("fid")%>').text('NotTrusted');--%>
                }
        );

    }
    function rate(fid, score) {
        $.post(
                '<%=request.getContextPath()%>/UserAction/opinion.jsp',
                {fid: fid, score: score},
                function (data) {
                    alert(data);
                    location.reload(true);
                    <%--if (score == 0) {--%>
                        <%--$('#usage-level-<%=request.getParameter("fid")%>').text("Useless");--%>
                    <%--}--%>
                    <%--if (score == 1) {--%>
                        <%--$('#usage-level-<%=request.getParameter("fid")%>').text("Useful");--%>
                    <%--}--%>
                    <%--if (score == 2) {--%>
                        <%--$('#usage-level-<%=request.getParameter("fid")%>').text("Very useful");--%>
                    <%--}--%>
                }
        );
    }
</script>
