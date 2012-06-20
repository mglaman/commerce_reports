<?php if (!empty($block['#children'])) {
  $attributes = array(
    'class' => array('commerce-reports-dashboard-block'),
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
    $sectionWidth =  floor((1. / (count($block['#visible']))) * 100);
  
    foreach ($block['sections'] as $name => $render) {
      if (($name != '#children') && ($name != '#printed')) { 
        $class = array('section');
        
        if (in_array($name, array_values($block['#visible']), TRUE)) {
          $class[] = 'visible';
        }
        
        if (!empty($render['#width'])) {
          $width = $render['#width'];
        } else {
          $width = $sectionWidth;
        }
  ?>
        <div<?php print drupal_attributes(array('class' => $class, 'data-section' => $name, 'style' => 'width: ' . $width . '%')) ?>><?php print $render['#children']; ?></div>
  <?php
      }
    } 
  ?>
</div>
<?php } ?>
