<%@ page import="acmdb.Util" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="acmdb.Row" %>
<%@ page import="acmdb.BrowsingPOI" %>
<%@ page import="acmdb.User" %><%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/9
  Time: 下午5:21
  To change this template use File | Settings | File Templates.
--%>
<%
    if (session.getAttribute("login") == null) {
        out.println("Please login first!");
    }
    User user = (User) session.getAttribute("User");
    double ge;
    try {
        ge = Double.parseDouble(request.getParameter("ge"));
    } catch (Exception e) {
        ge = -1;
    }
    double le;
    try {
        le = Double.parseDouble(request.getParameter("le"));
    } catch (Exception e) {
        le = -1;
    }
    String address = request.getParameter("address");
    String keyword = request.getParameter("keyword");
    String category= request.getParameter("category");
    String order = request.getParameter("order");
    ArrayList<Row> pois = user.fetchPOI(ge, le, address, keyword, category, order);
    out.println(String.format("{%s, %s}", Util.toJsonElement("total", pois.size()), Util.toJsonElement("rows", pois)));
%>
