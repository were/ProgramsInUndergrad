<%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/7
  Time: 下午2:15
  To change this template use File | Settings | File Templates.
--%>

<%@ page import="acmdb.POI" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="acmdb.Util" %>
<%@ page import="acmdb.Row" %>
<%@ page import="java.util.List" %>

<%
    if (session.getAttribute("login") == null) {
        out.println("Fuck ur mother!");
        return ;
    }
    int pageNo = request.getParameter("page") == null ? 1 : Integer.parseInt(request.getParameter("page"));
    int rows = request.getParameter("rows") == null ? 10 : Integer.parseInt(request.getParameter("rows"));
    int offset = (pageNo - 1) * rows;
    System.out.println(rows + " " + pageNo);
    ArrayList<Row> pois = POI.fetch("");
    if (pois == null) {
        out.println("{" + Util.toJsonElement("res", "fetchFail") + "}");
        return ;
    }
    ArrayList<Row> resPois = new ArrayList<Row>();
    for (int i = offset; i < pageNo * rows && i < pois.size(); ++i) {
        resPois.add(pois.get(i));
    }
    out.println(String.format("{%s, %s}", Util.toJsonElement("total", pois.size()), Util.toJsonElement("rows", resPois)));
%>
