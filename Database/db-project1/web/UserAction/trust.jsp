<%@ page import="acmdb.User" %><%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/9
  Time: 上午4:24
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    if ("admin".equals(session.getAttribute("login"))) {
        out.print("Admin should not trust!");
        return ;
    }
    User user;
    if (session.getAttribute("User") == null) {
        out.print("Please login first!");
        return ;
    }
    user = (User) session.getAttribute("User");
    if (request.getParameter("uid") == null) {
        out.println("UID id lost!");
        return ;
    }
    User another;
    try {
        another = (User) User.fetch("uid=" + request.getParameter("uid")).get(0);
        if (another.uid == user.uid) {
            out.println("One cannot trust him(her)self");
            return ;
        }
    } catch (Exception e) {
        e.printStackTrace();
        out.println("Fetch User failed!");
        return ;
    }
    if (request.getParameter("trusted") == null) {
        out.println("Rating lost!");
        return ;
    }
    int trusted = Integer.parseInt(request.getParameter("trusted"));
%>
<%=user.trust(another, trusted)%>
