%% views/header.html %%
<h1>{{$title}}</h1>
<div class='inputs'>
    <form action="@@sample/edit@@" method="post">
        <input type="hidden" id="id" name="id" value="{{$record['id']}}" />
        <label for="field1">Field 1:</label>
        <input type="text" id="field1" name="field1" value="{{$record['field1']}}" />
        <label for="field2">Field 2:</label>
        <input type="text" id="field2" name="field2" value="{{$record['field2']}}" />
        <label for="field3">Field 3:</label>
        <input type="text" id="field3" name="field3" value="{{$record['field3']}}" />
        <input type="submit" value="Update" />
    <form>
</div>
<div class="clearboth">
    <p><a href="@@index@@"><< Back</a></p>
</div>
%% views/footer.html %%
