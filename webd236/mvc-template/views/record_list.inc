%% views/header.html %%
<h1>{{$title}}</h1>
<h2>List of Current Records</h2>
<table>
  <tr>
    <th>ACTION</td>
    <th>Field 1</th>
    <th>Field 2</th>
    <th>Field 3</th>
  </tr>
  [[ foreach ($records as $record) : ]]
  <tr>
    <td>
      <a href="@@sample/view/{{$record['id']}}@@">[View]</a>
      ||
      <a href="@@sample/edit/{{$record['id']}}@@">[Edit]</a>
      ||
      <a href="@@sample/delete/{{$record['id']}}@@">[Del]</a>
    </td>
    <td>{{$record['field1']}}</td>
    <td>{{$record['field2']}}</td>
    <td>{{$record['field3']}}</td>
  </tr>
  [[ endforeach; ]]
</table>

<hr />

<form action="@@sample/add@@" method="post">
<fieldset>
    <label for="field1">Field 1:</label>
    <input type="text" id="field1" name="field1" /><br />
    <label for="field2">Field 2:</label>
    <input type="text" id="field2" name="field2" /><br />
    <label for="field3">Field 3:</label>
    <input type="text" id="field3" name="field3" /><br />
    <input type="submit" value="Add New Record" />
</fieldset>
</form>

%% views/footer.html %%
