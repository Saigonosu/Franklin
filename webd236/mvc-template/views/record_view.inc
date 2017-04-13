%% views/header.html %%
<h1>{{$title}}</h1>
<div class='display'>
    <label>Field 1:</label>
    <div class='value'>{{$record['field1']}}</div>
    <label>Field 2:</label>
    <div class='value'>{{$record['field2']}}</div>
    <label>Field 3:</label>
    <div class='value'>{{$record['field3']}}</div>
</div>
<div class="clearboth">
    <p><a href="@@index@@"><< Back</a></p>
</div>
%% views/footer.html %%
