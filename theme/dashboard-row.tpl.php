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
?>
<div class="row">
<?php
  foreach ($row['items'] as $index => $item) {
    if (substr($index, 0, 1) != '#') {
      switch ($item['#width']) {
        case 3:
          $itemClass = 'twelvecol';
          break;
          
        case 2:
          $itemClass = 'eightcol';
          break;
          
        default:
          $itemClass = 'fourcol';
          break;
      }
      
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
