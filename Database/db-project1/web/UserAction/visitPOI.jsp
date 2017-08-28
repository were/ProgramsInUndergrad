<%@ page import="acmdb.User" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="acmdb.Row" %>
<%@ page import="acmdb.POI" %><%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/9
  Time: 上午12:07
  To change this template use File | Settings | File Templates.
--%>
<%
    if ("admin".equals(session.getAttribute("login"))) {
        out.println("Admin cannot visit!");
        return ;
    }
    if (session.getAttribute("login") == null) {
        out.println("U should login first!");
        return ;
    }
    if (request.getParameter("pid") == null) {
        out.println("POI ID lost!");
        return ;
    }
    ArrayList<Row> poiList = POI.fetch("pid=" + request.getParameter("pid"));
    if (poiList.size() != 1) {
        out.println("No such POI!");
        return ;
    }
    if (request.getParameter("cost") == null) {
        out.println("How much did u spend?");
        return ;
    }
    if (request.getParameter("cnt") == null) {
        out.println("Ghost went ");
        return ;
    }
%>
<%=
    ((User) session.getAttribute("User")).visit((POI) poiList.get(0), Double.parseDouble(request.getParameter("cost")), Integer.parseInt(request.getParameter("cnt")))
%>
