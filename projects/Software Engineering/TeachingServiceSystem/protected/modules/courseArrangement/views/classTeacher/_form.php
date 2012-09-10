<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'class-teacher-form',
	'enableAjaxValidation'=>false,
)); ?>

	<p class="note">Fields with <span class="required">*</span> are required.</p>

	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'id'); ?>
		<?php echo $form->textField($model,'id',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'teacherid'); ?>
		<?php echo $form->textField($model,'teacherid',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'teacherid'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'classid'); ?>
		<?php echo $form->textField($model,'classid',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'classid'); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? 'Create' : 'Save'); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->