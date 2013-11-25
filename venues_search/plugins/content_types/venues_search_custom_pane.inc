<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Venues Zip Search'),
  'description' => t('Search venues via zip.'),
  'category' => t('Venues Search'),
  'edit form' => 'venues_search_zip_pane_edit_form',
  'render callback' => 'venues_search_zip_pane_render',
  'admin info' => 'venues_search_zip_pane_admin_info',
  'defaults' => array(
    'username' => 'wiifm',
    'tweets_to_show' => 5,
  )
);

/**
 * 'admin info' callback for panel pane.
 */
function venues_search_zip_pane_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
    $block->content = t('Showing @tweets_to_show tweets from <em>@@username</em>.', array(
      '@tweets_to_show' => $conf['tweets_to_show'],
      '@username' => $conf['username'],
    ));
    return $block;
  }
}

/**
 * 'Edit form' callback for the content type.
 */
function venues_search_zip_pane_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  return $form;
}

/**
 * The submit form stores the data in $conf.
 */
function venues_search_zip_pane_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function venues_search_zip_pane_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();

  // initial content is blank
  $block->title = '';
  // Add in the content
  $block->content .= '
<form action="venues" method="get" id="search-block-form">
<input type="text" name="field_geofield_distance[origin]" placeholder="City, State, or Zip" size="15">
<input type="submit" id="edit-submit" name="op" value="search" class="form-submit">
</form>

  ';

  return $block;
}
