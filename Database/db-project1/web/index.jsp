<%
    if (session.getAttribute("login") != null) {
        //out.println("From index!<br>");
%>
        <%@include file="./frontend/signed.jsp"%>
<%
        return ;
    }
    if ("success".equals(request.getParameter("register"))) {
        out.println("You have successfully signed in, please login.");
    }
%>
<script src="<%=request.getContextPath()%>/script/jquery.js"></script>
<script src="<%=request.getContextPath()%>/script/sha1.js"></script>
<script>
    $(document).ready(
            function () {
                $("#login").blur(
                        function () {
                            if ($("#login").val() == "") {
                                $("#login-error").text("Login cannot be empty");
                            } else {
                                $("#login-error").text("");
                            }
                        }
                );
                $("#password").blur(
                        function () {
                            if ($("#password").val() == "") {
                                $("#password-error").text("Password cannot be empty");
                            } else {
                                $("#password-error").text("");
                            }
                        }
                );
                $("#reset").click(
                        function () {
                            $("#password").val("");
                            $("#password-error").text("Password cannot be empty");
                            $("#login").val("");
                            $("#login-error").text("Login cannot be empty");
                        }
                );
                $("#login-but").click(
                        function () {
                            if ($("#login-error").text() != "") {
                                alert($("#login-error").text());
                                return ;
                            }
                            if ($("#password-error").text() != "") {
                                alert($("#password-error").text());
                                return ;
                            }
                            window.location = "<%=request.getContextPath()%>/UserAction/login.jsp?login=" + $("#login").val() +
                                                            "&password=" + hex_sha1($("#password").val());
                        }
                );
            }
    );

</script>

<script>
    $(document).ready(function () {
<%  if (request.getParameter("userNotFound") != null) { %>
        $("#login-error").text("User not found!");
<%  } else {%>
        if ($("#login").val() == "") {
            $("#login-error").text("Login cannot be empty");
        }
<%  }
    if (request.getParameter("passwordError") != null) { %>
        $("#password-error").text("Password error!");
<%  } else {%>
        if ($("#password").val() == "") {
            $("#password-error").text("Password cannot be empty");
        }
<%  }%>
    });
</script>

<table>
<tr><td>login: </td><td><input type="input" id="login" value="<%=request.getParameter("login") == null ? "" : request.getParameter("login")%>"/> </td><td id="login-error"></td></tr>
<tr><td>password: </td><td><input type="password" id="password" value=""/> </td><td id="password-error"></td></tr>
<tr><td><input type="button" value="login" id="login-but"/> </td>
    <td><input type="button" value="reset" id="reset"/> </td>
<td><a href="<%=request.getContextPath()%>/frontend/register.jsp"> <input type="button" value="register" /> </a></td></tr>
</table>

Due to the encoding rule, no chinese supported...
