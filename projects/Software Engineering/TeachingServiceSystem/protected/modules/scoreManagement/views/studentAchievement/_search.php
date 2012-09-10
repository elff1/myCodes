<div class="wide form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'action'=>Yii::app()->createUrl($this->route),
	'method'=>'get',
)); ?>


	<div class="row">
		<?php echo $form->label($model,'gpa_major'); ?>
		<?php echo $form->textField($model,'gpa_major'); ?>
	</div>

	<div class="row">
		<?php echo $form->label($model,'gpa_total'); ?>
		<?php echo $form->textField($model,'gpa_total'); ?>
	</div>

	<div class="row">
		<?php echo $form->label($model,'credit_total'); ?>
		<?php echo $form->textField($model,'credit_total'); ?>
	</div>

	<div class="row">
		<?php echo $form->label($model,'credit_achieve'); ?>
		<?php echo $form->textField($model,'credit_achieve'); ?>
	</div>

	<div class="row">
		<?php echo $form->label($model,'credit_major_total'); ?>
		<?php echo $form->textField($model,'credit_major_total'); ?>
	</div>

	<div class="row">
		<?php echo $form->label($model,'credit_major_achieve'); ?>
		<?php echo $form->textField($model,'credit_major_achieve'); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton('Search'); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- search-form -->