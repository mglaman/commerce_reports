<?php if (!empty($block['#children'])) { ?>
<div class='commerce-reports-dashboard-block'>
  <div class='header'>
    <h1><?php print $block['title']; ?></h1>
    <span>(from <?php print $block['report']; ?>)</span>
    <?php if (!empty($block['operations'])) { ?>
    <div class='operations'>
      <?php print $block['operations']; ?>
    </div>
    <?php } ?>
  </div>
  <?php
    $sectionWidth =  floor((1. / (count($block['visible']) - 2)) * 100);
  
    foreach ($block['sections'] as $name => $render) {
      if (($name != '#children') && ($name != '#printed')) { 
        $class = array('section');
        
        if (in_array($name, array_values($block['visible']), TRUE)) {
          $class[] = 'visible';
        } ?>
        <div<?php print drupal_attributes(array('class' => $class, 'data-section' => $name, 'style' => 'width: ' . $sectionWidth . '%')) ?>><?php print $render['#children']; ?></div>
      <?php
      }
    } 
  ?>
</div>
<?php } ?>
