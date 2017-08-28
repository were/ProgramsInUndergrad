<%@ page import="acmdb.User" %><%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/7
  Time: 下午4:29
  To change this template use File | Settings | File Templates.
--%>
<script src="<%=request.getContextPath()%>/script/jquery.js"></script>
<%
    User user = new User(
            -1,
            (String) request.getParameter("login"),
            (String) request.getParameter("username"),
            (String) request.getParameter("phoneno"),
            (String) request.getParameter("password"),
            (String) request.getParameter("address")
    );
    String res = user.register();
    if (res == "success") {%>
        <script>
            $(document).ready(
                    function () {
                        window.location = "../index.jsp";
                    }
            );
        </script>
<%  } else {%>
        <script>
            $(document).ready(
                    function () {
                        window.location = "<%=request.getContextPath()%>/frontend/register.jsp?"
                                +                 "<%=res%>&"
                                +    "login=<%=user.login%>&"
                                + "username=<%=user.uname%>&"
                                +"phoneno=<%=user.phoneNo%>&"
                                + "address=<%=user.address%>";
                    }
            );
        </script>
<%  }%>
