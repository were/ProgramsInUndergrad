<%--
  Created by IntelliJ IDEA.
  User: Mars
  Date: 16/6/11
  Time: 下午4:10
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="acmdb.*" %>
<%
    if (session.getAttribute("login") == null) {
        out.println("Please login first!");
    }
    ArrayList<Row> pois = MHJ.fetchHighRatedPOI();
    out.println(String.format("{%s, %s}", Util.toJsonElement("total", pois.size()), Util.toJsonElement("rows", pois)));
%>


