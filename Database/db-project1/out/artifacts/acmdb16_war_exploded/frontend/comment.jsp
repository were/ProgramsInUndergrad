<%--
  Created by IntelliJ IDEA.
  User: were
  Date: 16/6/10
  Time: 下午7:58
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>


<head>
    <script src="<%=request.getContextPath()%>/script/jquery.js"></script>
    <link rel="stylesheet" type="text/css" href="<%=request.getContextPath()%>/themes/default/easyui.css">
    <link rel="stylesheet" type="text/css" href="<%=request.getContextPath()%>/themes/icon.css">
    <script type="text/javascript" src="<%=request.getContextPath()%>/script/jquery.min.js"></script>
    <script type="text/javascript" src="<%=request.getContextPath()%>/script/jquery.easyui.min.js"></script>
    <script type="text/javascript" src="<%=request.getContextPath()%>/script/datagrid-detailview.js"></script>
</head>

<table id="comment-dg-<%=request.getParameter("pid")%>" title="Comments" class="easyui-datagrid" style="width:800px;height:500px;"
       rownumbers="true" fitColumns="true" singleSelect="true" >
    <thead>
    <tr>
        <th field="from" width="12" >Feedback by</th>
        <th field="score" width="12">Rating</th>
        <th field="opinion" width="12">Other Opnion</th>
    </tr>
    </thead>
</table>


<a class="easyui-linkbutton" iconCls="icon-ok" href="<%=request.getContextPath()%>/index.jsp">Return</a>

<script>
    $('#comment-dg-<%=request.getParameter("pid")%>').datagrid({
        view: detailview,
        url: "<%=request.getContextPath()%>/POIAction/getFeedback.jsp?pid=<%=request.getParameter("pid")%>",
        detailFormatter: function () {
            return '<div class="ddv"></div>';
        },
        fitColumns: true,
        onExpandRow: function(index,row){
            var ddv = $(this).datagrid('getRowDetail',index).find('div.ddv');
            ddv.panel({
                border:true,
                cache:true,
                href:'<%=request.getContextPath()%>/widget/showComment.jsp?pid='+row.pid+'&cmt='+row.cmt+'&uid='+row.uid+'&fid='+row.fid,
                onLoad:function(){
                    $('#comment-dg-<%=request.getParameter("pid")%>').datagrid('fixDetailRowHeight', index);
                    $('#comment-dg-<%=request.getParameter("pid")%>').datagrid('selectRow', index);
                    $('#comment-dg-<%=request.getParameter("pid")%>').datagrid('getRowDetail', index).find('form').form('load',row);
                }
            });
            $('#comment-dg-<%=request.getParameter("pid")%>').datagrid('fixDetailRowHeight',index);
        }
    });
</script>


<table id="comment-useful-dg-<%=request.getParameter("pid")%>" title="Most Useful" class="easyui-datagrid" style="width:800px;height:500px;"
       rownumbers="true" fitColumns="true" singleSelect="true" >
    <thead>
    <tr>
        <th field="from" width="12" >Feedback by</th>
        <th field="score" width="12">Rating</th>
        <th field="opinion" width="12">Other Opnion</th>
    </tr>
    </thead>
</table>


<a class="easyui-linkbutton" iconCls="icon-ok" href="<%=request.getContextPath()%>/index.jsp">Return</a>

<script>
    $('#comment-useful-dg-<%=request.getParameter("pid")%>').datagrid({
        view: detailview,
        url: "<%=request.getContextPath()%>/POIAction/getUsefulFeedback.jsp?pid=<%=request.getParameter("pid")%>",
        detailFormatter: function () {
            return '<div class="ddv"></div>';
        },
        fitColumns: true,
        onExpandRow: function(index,row){
            var ddv = $(this).datagrid('getRowDetail',index).find('div.ddv');
            ddv.panel({
                border:true,
                cache:true,
                href:'<%=request.getContextPath()%>/widget/showComment.jsp?pid='+row.pid+'&cmt='+row.cmt+'&uid='+row.uid+'&fid='+row.fid,
                onLoad:function(){
                    $('#comment-useful-dg-<%=request.getParameter("pid")%>').datagrid('fixDetailRowHeight', index);
                    $('#comment-useful-dg-<%=request.getParameter("pid")%>').datagrid('selectRow', index);
                    $('#comment-useful-dg-<%=request.getParameter("pid")%>').datagrid('getRowDetail', index).find('form').form('load',row);
                }
            });
            $('#comment-useful-dg-<%=request.getParameter("pid")%>').datagrid('fixDetailRowHeight',index);
        }
    });
</script>
