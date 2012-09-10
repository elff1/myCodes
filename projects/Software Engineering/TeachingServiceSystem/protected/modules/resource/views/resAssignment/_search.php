<div class="wide form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'action'=>Yii::app()->createUrl($this->route),
	'method'=>'get',
)); ?>

	<div class="row">
		<?php echo $form->label($model,'id'); ?>
		<?php echo $form->textField($model,'id',array('size'=>11,'maxlength'=>11)); ?>
	</div>

	<div class="row">
		<?php echo $form->label($model,'teachingclass_id'); ?>
		<?php echo $form->textField($model,'teachingclass_id',array('size'=>11,'maxlength'=>11)); ?>
	</div>

	<div class="row">
		<?php echo $form->label($model,'resource_id'); ?>
		<?php echo $form->textField($model,'resource_id',array('size'=>11,'maxlength'=>11)); ?>
	</div>

	<div class="row">
		<?php echo $form->label($model,'dead_line'); ?>
		<?php echo $form->textField($model,'dead_line'); ?>
	</div>

	<div class="row">
		<?php echo $form->label($model,'is_published'); ?>
		<?php echo $form->textField($model,'is_published'); ?>
	</div>

	<div class="row">
		<?php echo $form->label($model,'teacher_id'); ?>
		<?php echo $form->textField($model,'teacher_id'); ?>
	</div>

	<div class="row">
		<?php echo $form->label($model,'requirement'); ?>
		<?php echo $form->textField($model,'requirement',array('size'=>60,'maxlength'=>2048)); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton('Search'); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- search-form -->
