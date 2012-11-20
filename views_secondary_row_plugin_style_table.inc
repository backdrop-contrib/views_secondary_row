<?php
/**
 * @file
 * Contains this module's extended table style plugin, which allows rows
 * to be broken into two.
 */

class views_secondary_row_plugin_style_table extends views_plugin_style_table {
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $handlers = $this->display->handler->get_handlers('field');
    if (empty($handlers)) {
      $form['error_markup'] = array(
        '#markup' => '<div class="error messages">' . t('You need at least one field before you can configure your table settings') . '</div>',
      );
      return;
    }

    $form['#theme'] = 'views_secondary_row_style_plugin_table';

    $columns = $this->sanitize_columns($this->options['columns']);

    // Create an array of allowed columns from the data we know:
    $field_names = array(t('None')) + $this->display->handler->get_field_labels();

    foreach ($columns as $field => $column) {
      $safe = str_replace(array('][', '_', ' '), '-', $field);
      // the $id of the column for dependency checking.
      $id = 'edit-style-options-columns-' . $safe;

      $form['info'][$field]['break'] = array(
        '#type' => 'select',
        '#default_value' => isset($this->options['info'][$field]['break']) ? $this->options['info'][$field]['break'] : '',
        '#options' => $field_names,
        '#dependency' => array($id => array($field)),
      );
      $form['info'][$field]['colspan'] = array(
        '#type' => 'textfield',
        '#default_value' => isset($this->options['info'][$field]['colspan']) ? $this->options['info'][$field]['colspan'] : '',
        '#size' => 5,
      );
    }
  }
}
