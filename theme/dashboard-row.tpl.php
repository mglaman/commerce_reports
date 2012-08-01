<?php

/**
 * @file
 * Template file returns HTML for a single row on the Commerce Reports dashboard.
 *
 * @param $row
 *
 * @return
 *   The row div.
 */
 
$itemClass = '';

switch (count($row['items']) - 2) {
  case 3:
    $itemClass = 'fourcol';
    break;
    
  case 1:
    $itemClass = 'twelvecol';
    break;
    
  default: 
    print count($row['items']);
}
?>
<div class="row">
<?php
  foreach ($row['items'] as $index => $item) {
    if (substr($index, 0, 1) != '#') { 
      if ($index == count($row['items']) - 3) {
        $itemClass .= ' last';
      }
    ?>
      <div class="<?php print $itemClass; ?>">
        <?php print $item['#children']; ?>
      </div>
<?php
    }
  }
?>
</div>
