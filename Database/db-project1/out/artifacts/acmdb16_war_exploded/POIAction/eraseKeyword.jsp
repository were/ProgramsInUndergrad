<%@ page import="acmdb.POI" %><%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/8
  Time: 下午10:39
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    if (!"admin".equals(session.getAttribute("login"))) {
        out.println("U have no authority to access!");
        return;
    }
    if (request.getParameter("pid") == null) {
        out.println("pid lost!");
        return;
    }
    if (request.getParameter("keyword") == null) {
        out.println("keyword lost");
        return;
    }
%>

<%=
POI.eraseKeyword(
        Integer.parseInt(request.getParameter("pid")),
        request.getParameter("keyword")
)
%>
