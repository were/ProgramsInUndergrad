<%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/8
  Time: 下午9:55
  To change this template use File | Settings | File Templates.
--%>
<%@ page import="acmdb.POI" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
        if (!"admin".equals(session.getAttribute("login"))) {
                out.println("U have no authority to access!");
                return;
        }
        if (request.getParameter("keyword") == null) {
                out.println("Keyword lost!");
        }
%>

<%=
        POI.addKeyword(
                Integer.parseInt(request.getParameter("pid")),
                request.getParameter("keyword")
        )
%>
