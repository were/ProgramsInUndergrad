<%@ page import="acmdb.User" %>
<%@ page import="acmdb.POI" %><%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/9
  Time: 上午3:58
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    if ("admin".equals(session.getAttribute("login"))) {
        out.print("Admin should not feedback!");
        return ;
    }
    User user;
    if (session.getAttribute("User") == null) {
        out.print("Please login first!");
        return ;
    }
    user = (User) session.getAttribute("User");
    if (request.getParameter("pid") == null) {
        out.println("POI id lost!");
        return ;
    }
    POI poi;
    try {
        poi = (POI) POI.fetch("pid=" + request.getParameter("pid")).get(0);
    } catch (Exception e) {
        e.printStackTrace();
        out.println("Fetch POI failed!");
        return ;
    }
    int score;
    if (request.getParameter("score") == null) {
        out.println("Rate score lost!");
        return ;
    }
    score = Integer.parseInt(request.getParameter("score"));
    if (score < 0 || score > 10) {
        out.println("Score out of range");
        return ;
    }
    String comment = request.getParameter("comment") == null ? "" : request.getParameter("comment");
%>
<%=user.feedback(poi, comment, score)%>
