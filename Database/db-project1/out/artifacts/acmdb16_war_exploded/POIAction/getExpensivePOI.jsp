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
    if (session.getAttribute("login") == null) {
        out.println("Please login first!");
    }
    ArrayList<Row> pois = MHJ.fetchExpensivePOI();
    out.println(String.format("{%s, %s}", Util.toJsonElement("total", pois.size()), Util.toJsonElement("rows", pois)));
%>

