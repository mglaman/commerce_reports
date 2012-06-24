<?php if (!empty($block['#children'])) {
  $attributes = array(
    'class' => array('commerce-reports-dashboard-block', 'commerce-reports-dashboard-' . $block['#name'] . '-block'),
  );
  
  if (!empty($block['#width'])) {
    $attributes['style'] = 'width: ' . $block['#width'] . '%';
  }
?>
<div<?php print drupal_attributes($attributes); ?>>
  <div class='header'>
    <h1><?php print $block['#title']; ?></h1>
    <?php if (!empty($block['#report'])) { ?>
    <span>(from <?php print $block['#report']; ?>)</span>
    <?php } ?>
    <?php if (!empty($block['#operations'])) { ?>
    <div class='operations'>
      <?php print $block['#operations']; ?>
    </div>
    <?php } ?>
  </div>
  <?php
    $sectionWidth =  (1. / (count($block['#visible']))) * 100;
  
    $i = 0;
    foreach ($block['sections'] as $name => $render) {
      if (($name != '#children') && ($name != '#printed')) { 
        $class = array('section', 'section-' . $name);
        
        if (in_array($name, array_values($block['#visible']), TRUE)) {
          $class[] = 'visible';
        }
        
        if (!empty($render['#width'])) {
          $width = $render['#width'];
        } else {
          $width = floor($sectionWidth);
        }
  ?>
        <div<?php print drupal_attributes(array('class' => $class, 'data-section' => $name, 'style' => 'width: ' . $width . '%')) ?>><?php print $render['#children']; ?></div>
  <?php
        $i ++;
      }
    } 
  ?>
</div>
<?php } ?>
