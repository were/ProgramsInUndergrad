<%@ page import="java.util.ArrayList" %>
<%@ page import="acmdb.Row" %>
<%@ page import="acmdb.MHJ" %>
<%@ page import="acmdb.Util" %>
<%--  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/11
  Time: 上午2:04
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    if (session.getAttribute("login") == null) {
        out.println("Please login first!");
        return ;
    }
    if (request.getParameter("pid") == null) {
        out.println("PID lost!");
        return ;
    }
    ArrayList<Row> pois = MHJ.suggest(Integer.parseInt(request.getParameter("pid")));
    out.println(String.format("{%s, %s}", Util.toJsonElement("total", pois.size()), Util.toJsonElement("rows", pois)));
%>
