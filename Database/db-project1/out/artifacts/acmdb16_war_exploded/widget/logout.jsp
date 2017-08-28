<%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/6
  Time: 下午11:51
  To change this template use File | Settings | File Templates.
--%>
<%
    if (session.getAttribute("login") == null) {
        return ;
    }
%>
<a href="<%=request.getContextPath()%>/UserAction/logout.jsp"><input type="button" value="logout"/></a>
