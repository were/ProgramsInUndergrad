<%@ page import="acmdb.Connector" %>
<%@ page import="java.sql.SQLException" %>
<%@ page import="java.sql.ResultSet" %>
<%@ page import="acmdb.User" %>
<html>

<head>
    <script src="<%=request.getContextPath()%>/script/jquery.js"></script>
    <script src="<%=request.getContextPath()%>/script/sha1.js"></script>
</head>
<%
    User user = new User(
            -1,
            (String) request.getParameter("login"),
            (String) request.getParameter("username"),
            (String) request.getParameter("phoneno"),
            (String) request.getParameter("password"),
            (String) request.getParameter("address")
    );
    String error = request.getParameter("error");
    error = error == null ? "" : error;
    String loginError = "";
    if (error.equals("loginEmpty")) {
        loginError = "Login name cannot be empty";
    }
    if (error.equals("loginExisted")) {
        loginError = "Such login name alread existed!";
    }
%>
<script>
    function inCharSet(char) {
        if (char >= 'A' && char <= 'Z') {
            return true;
        }
        if (char >= 'a' && char <= 'z') {
            return true;
        }
        if (char >= '0' && char <= '9') {
            return true;
        }
        return false;
    }

    function goodString(string) {
        for (var i = 0; i < string.length; ++i) {
            if (!inCharSet(string[i])) {
                return false;
            }
        }
        return true;
    }
    $(document).ready(
            function () {
                $("#login-error").text("<%=loginError%>");
                $("#password-error").text("Password cannot be empty");
                $("#confirm-error").text("");
                $("#login").blur(
                        function () {
                            var login = $("#login").val();
                            if (login == "") {
                                $("#login-error").text("Login name cannot be empty");
                            } else if (login.length < 4) {
                                $("#login-error").text("Login name must have length 4 at least");
                            } else if (!goodString(login)) {
                                $("#login-error").text("Only 0-9, A-Z, and a-z can be used as login name");
                            } else if (login.length > 10) {
                                $("#login-error").text("Login in name cannot be longer than 10");
                            } else {
                                $("#login-error").text("");
                            }
                        }
                );
                $("#password").blur(
                        function () {
                            var password = $("#password").val();
                            if (password == "") {
                                $("#password-error").text("Password cannot be empty");
                            } else if (password.length < 4) {
                                $("#password-error").text("Password must at least have length 4");
                            } else if (!goodString(password)) {
                                $("#password-error").text("Only 0-9, A-Z, and a-z can be used as password");
                            } else if (password.length > 16) {
                                $("#password-error").text("Password cannot be longer than 16!");
                            } else {
                                $("#password-error").text("");
                            }
                        }
                );
                $("#confirm-pwd").blur(
                        function () {
                            var password = $("#password").val();
                            var confirm = $("#confirm-pwd").val();
                            if (password != confirm) {
                                $("#password-error").text("Confirm password should be identical to the origin password!");
                            } else {
                                $("#password-error").text("");
                            }
                        }
                );
                $("#phoneno").blur(
                        function () {
                            var phoneno = $("#phoneno").val();
                            for (var i = 0; i < phoneno.length; ++i) {
                                if (phoneno[i] < '0' || phoneno[i] > '9') {
                                    $("#phoneno-error").text("Only numbers can exist in phone number!");
                                    return ;
                                }
                            }
                            $("#phoneno-error").text("");
                        }
                );
                $("#submit-info").click(
                        function () {
                            if ($("#login-error").text() != "") {
                                alert($("#login-error").text());
                                return ;
                            }
                            if ($("#password-error").text() != "") {
                                alert($("#password-error").text());
                                return ;
                            }
                            if ($("#confirm-error").text() != "") {
                                alert($("#confirm-error").text());
                                return ;
                            }
                            if ($('#phoneno-error').text() != "") {
                                alert($("#phoneno-error").text());
                                return ;
                            }
                            window.location = "<%=request.getContextPath()%>/UserAction/addUser.jsp?login=" + $("#login").val() +
                                                               "&username=" + $("#username").val() +
                                                               "&password=" + hex_sha1($("#password").val()) +
                                                                    "&url=" + $("#url").val() +
                                                                "&phoneno=" + $("#phoneno").val() +
                                                                "&address=" + $("#address").val();
                        }
                );
            }
    );
</script>

<body>

<table>
    <tr> <td>Login Name: </td> <td> <input type=text id="login" value="<%=user.login%>" size=20> </input> </td> <td id="login-error"><%=loginError%></td> </tr>
    <tr> <td>User Name: </td> <td> <input type=text id="username" value="<%=user.uname%>" size=20> </input> </td> <td></td> </tr>
    <tr> <td>Password: </td> <td><input type=password id="password" value="" size=20> </input> </td> <td id="password-error"> </td></tr>
    <tr> <td>Confirm Password: </td> <td><input type=password id="confirm-pwd" value="" size=20> </input> </td> <td id="confirm-error"> </td></tr>
    <tr> <td>Phone Number: </td><td> <input type=text id="phoneno" value="<%=user.phoneNo%>" size=20> </input> </td> <td id="phoneno-error"></td></tr>
    <tr> <td>Address: </td><td> <input type=text id="address" value="<%=user.address%>" size=20> </input> </td> <td></td></tr>
    <tr> <td> <input id="submit-info" type=button value="submit" > </input> </td> <td> </td> <td></td> </tr>
</table>

</body>
</html>

