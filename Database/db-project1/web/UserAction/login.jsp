<%@ page import="acmdb.*" %>
<%@ page import="java.sql.*" %><%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/6
  Time: 下午7:47
  To change this template use File | Settings | File Templates.
--%>
<%  if (session.getAttribute("login") != null) {
        out.println("login from login.jsp");%>
        <%@include file="../frontend/signed.jsp"%>
<%  } else {
        String loginRes = User.login(request.getParameter("login"), request.getParameter("password"));
        if (loginRes.equals("success")) {
            session.setAttribute("login", request.getParameter("login"));
            session.setAttribute("User", User.fetch("login='" + request.getParameter("login") + "'").get(0));
        }%>
        <script src="<%=request.getContextPath()%>/script/jquery.js"></script>
        <script>
            $(document).ready(
                    function () {
                        window.location = "../index.jsp";
                    }
            );
        </script>
<%
    }
%>
