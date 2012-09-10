<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'temp-request-form',
	'enableAjaxValidation'=>false,
)); ?>

	<p class="note">Fields with <span class="required">*</span> are required.</p>

	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'teacher_id'); ?>
		<?php echo $form->textField($model,'teacher_id',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'teacher_id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'teachingclass_id'); ?>
		<?php echo $form->textField($model,'teachingclass_id',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'teachingclass_id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'student_id'); ?>
		<?php echo $form->textField($model,'student_id',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'student_id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'score'); ?>
		<?php echo $form->textField($model,'score'); ?>
		<?php echo $form->error($model,'score'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'reason'); ?>
		<?php echo $form->textField($model,'reason',array('size'=>60,'maxlength'=>512)); ?>
		<?php echo $form->error($model,'reason'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'result'); ?>
		<?php echo $form->textField($model,'result'); ?>
		<?php echo $form->error($model,'result'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'is_handle'); ?>
		<?php echo $form->textField($model,'is_handle'); ?>
		<?php echo $form->error($model,'is_handle'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'is_ack'); ?>
		<?php echo $form->textField($model,'is_ack'); ?>
		<?php echo $form->error($model,'is_ack'); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? 'Create' : 'Save'); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->