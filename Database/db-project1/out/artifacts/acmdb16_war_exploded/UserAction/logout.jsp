<%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/6
  Time: 下午11:45
  To change this template use File | Settings | File Templates.
--%>
<script src="<%=request.getContextPath()%>/script/jquery.js"></script>
<%  session.setAttribute("login", null);%>
<script>
    $(document).ready(
            function () {
                window.location = "../index.jsp";
            }
    );
</script>

