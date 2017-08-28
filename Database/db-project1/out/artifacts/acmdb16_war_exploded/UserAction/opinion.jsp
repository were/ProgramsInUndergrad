<%@ page import="acmdb.User" %>
<%@ page import="acmdb.Connector" %>
<%@ page import="java.sql.ResultSet" %><%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/9
  Time: 上午4:12
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
    if (request.getParameter("fid") == null) {
        out.println("Feedback id lost!");
        return ;
    }
    try {
        ResultSet res = new Connector().stmt.executeQuery("SELECT * FROM Feedback WHERE fid=" + request.getParameter("fid"));
        if (!res.next()) {
            out.println("No such feedback!");
            return ;
        } else {
            if (res.getInt("uid") == user.uid) {
                out.println("No one can rate his/her own!");
                return ;
            }
        }
    } catch (Exception e) {
        e.printStackTrace();
        out.println("SQL Failed");
        return ;
    }
    int fid = Integer.parseInt(request.getParameter("fid"));
    int score;
    if (request.getParameter("score") == null) {
        out.println("Rate score lost!");
        return ;
    }
    score = Integer.parseInt(request.getParameter("score"));
    if (score < 0 || score > 3) {
        out.println("Score out of range");
        return ;
    }
%>
<%=user.opinion(fid, score)%>
