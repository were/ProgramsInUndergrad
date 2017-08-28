<%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/6
  Time: 下午11:59
  To change this template use File | Settings | File Templates.
--%>
<%
    if (session.getAttribute("login") == null) {
        return ;
    }
    //String uname = ((User) session.getAttribute("User")).uname;
%>

<%@include file="../widget/logout.jsp"%>

Welcome <%=session.getAttribute("login")%>!

<%  if (session.getAttribute("login").equals("admin")) { %>
        <%@include file="admin.jsp"%>
<%  } else {%>
        <%@include file="browse.jsp"%>
<%  }%>
