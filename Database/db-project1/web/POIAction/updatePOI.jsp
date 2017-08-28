<%@ page import="acmdb.Connector" %>
<%@ page import="java.sql.SQLException" %>
<%@ page import="acmdb.POI" %><%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/7
  Time: 上午1:16
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    if (!"admin".equals(session.getAttribute("login"))) {
        out.println("What do you want to do?");
        return ;
    }
    if (request.getParameter("pid") != null) {
        String msg = POI.updatePOI(
                new POI(
                        Integer.parseInt(request.getParameter("pid")),
                        request.getParameter("pname"),
                        request.getParameter("address"),
                        request.getParameter("phoneno"),
                        Integer.parseInt(request.getParameter("year")),
                        request.getParameter("category"),
                        request.getParameter("url"),
                        request.getParameter("operation"),
                        Double.parseDouble(request.getParameter("price"))
                )
        );
        out.println(msg);
        return ;
    }
    try {
        POI.updatePOI(
                new POI(
                        -1,
                        request.getParameter("pname"),
                        request.getParameter("address"),
                        request.getParameter("phoneno"),
                        Integer.parseInt(request.getParameter("year")),
                        request.getParameter("category"),
                        request.getParameter("url"),
                        request.getParameter("operation"),
                        Double.parseDouble(request.getParameter("price"))
                )
        );
    } catch (Exception T_T) {%>
        <script src="<%=request.getContextPath()%>/script/jquery.js"></script>
        <script>
            window.location="<%=request.getContextPath()%>/frontend/signed.jsp?error=addFail";
        </script>
<%  }%>
<script src="<%=request.getContextPath()%>/script/jquery.js"></script>
<script>
    $(document).ready(
            function () {
                window.location = "<%=request.getContextPath()%>/frontend/signed.jsp";
            }
    );
</script>
