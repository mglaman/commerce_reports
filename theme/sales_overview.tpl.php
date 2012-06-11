<table class="sales-overview">
  <caption><?php print $date['label']; ?></caption>
  
  <tr>
    <th class="count"><a href="#">Sales</a></th>
    <th class="sum"><a href="#">Gross</a></th>
    <th class="average"><a href="#">Average</a></th>
  </tr>
  
  <?php foreach ($data as $currency => $row) { ?>
  <tr>
    <td class="count"><?php print $row['count'] ?></td>
    <td class="sum"><?php print commerce_reports_currency_format($row['sum'], $currency) ?></td>
    <td class="average"><?php print commerce_reports_currency_format($row['average'], $currency) ?></td>
  </tr>
  <?php } ?>
</table>
