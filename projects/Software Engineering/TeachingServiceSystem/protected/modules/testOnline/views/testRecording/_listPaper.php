<div class="view">

<?php /*$form=$this->beginWidget('CActiveForm', array(
	'id'=>'list-paper-form',
	'enableAjaxValidation'=>false,
)); */?>

	<b><?php echo CHtml::encode($data->getAttributeLabel('question')); ?>:</b>
	<?php echo CHtml::encode($data->question); ?>
	<br />
	
	<b><?php if(!$data->type) echo CHtml::encode('A.'); ?></b>
	<?php if(!$data->type) echo CHtml::encode($data->selection_a); ?>
	<?php ?>
	<br />

	<b><?php if(!$data->type)echo CHtml::encode('B.'); ?></b>
	<?php if(!$data->type)echo CHtml::encode($data->selection_b); ?>
	<br />
	
	<b><?php if(!$data->type)echo CHtml::encode('C.'); ?></b>
	<?php if(!$data->type)echo CHtml::encode($data->selection_c); ?>
	<br />

	<b><?php if(!$data->type)echo CHtml::encode('D.'); ?></b>
	<?php if(!$data->type)echo CHtml::encode($data->selection_d); ?>
	<br />
	
</div>

