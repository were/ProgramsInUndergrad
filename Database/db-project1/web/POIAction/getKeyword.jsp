<%@ page import="acmdb.POI" %>
<%@ page import="acmdb.Util" %>
<%@ page import="java.util.Iterator" %>
<%@ page import="java.util.ArrayList" %><%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/8
  Time: 下午10:10
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    if (request.getParameter("pid") == null) {
        out.println("Pid lost!");
        return ;
    }
    int pid = Integer.parseInt(request.getParameter("pid"));
    if (POI.fetch(" pid=" + Integer.toString(pid)).size() == 0) {
        out.println("No such POI!");
    }
    ArrayList<String> keys = POI.fetchKeyword(pid);
    Iterator iter = keys.iterator();
    String rows = "[";
    while (iter.hasNext()) {
        String key = (String) iter.next();
        if (iter.hasNext()) {
            rows += "{" + Util.toJsonElement("text", key) + "},";
        } else {
            rows += "{" + Util.toJsonElement("text", key) + "}";
        }
    }
    rows += "]";
    out.println(rows);
    //out.println(String.format("{%s, \"rows\":%s}", Util.toJsonElement("total", keys.size()), rows));
%>
