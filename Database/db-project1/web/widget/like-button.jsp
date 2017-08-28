<%@ page import="acmdb.Connector" %>
<%@ page import="acmdb.User" %><%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/10
  Time: 上午3:07
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<%  if (((User) session.getAttribute("User")).isLike(Integer.parseInt(request.getParameter("pid")))) {%>
        <a class="easyui-linkbutton" iconCls="icon-add" id="like-<%=request.getParameter("pid")%>" plain="true" disabled="true">MyFavorite</a>
<%  } else {%>
        <a class="easyui-linkbutton" iconCls="icon-add" id="like-<%=request.getParameter("pid")%>" plain="true">MyFavorite</a>
<%  }%>
