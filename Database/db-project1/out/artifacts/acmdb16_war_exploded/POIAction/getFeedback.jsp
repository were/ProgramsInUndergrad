<%@ page import="java.util.ArrayList" %>
<%@ page import="acmdb.Row" %>
<%@ page import="acmdb.Feedback" %>
<%@ page import="acmdb.Util" %><%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/10
  Time: 下午7:37
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    if (session.getAttribute("login") == null) {
        out.print("Please login first!");
        return ;
    }
    if (request.getParameter("pid") == null) {
        out.print("PID lost!");
        return ;
    }
    ArrayList<Row> feedback = Feedback.fetch(Integer.parseInt(request.getParameter("pid")));

    out.println(String.format("{%s, %s}", Util.toJsonElement("total", feedback.size()), Util.toJsonElement("rows", feedback)));
%>
