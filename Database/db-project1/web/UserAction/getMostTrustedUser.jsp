<%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/11
  Time: 下午3:28
  To change this template use File | Settings | File Templates.
--%>
<%@ page import="java.util.ArrayList" %>
<%@ page import="acmdb.*" %>
<%
    if (!"admin".equals(session.getAttribute("login"))) {
            out.println("U have no authority to access!");
            return;
    }
    ArrayList<Row> users = MHJ.fetchMostTrustedUser();
    out.println(String.format("{%s, %s}", Util.toJsonElement("total", users.size()), Util.toJsonElement("rows", users)));
%>

