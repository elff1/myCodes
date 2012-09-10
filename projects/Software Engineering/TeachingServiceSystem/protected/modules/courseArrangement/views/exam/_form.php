<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'exam-form',
	'enableAjaxValidation'=>false,
)); ?>

	<p class="note">Fields with <span class="required">*</span> are required.</p>

	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'id'); ?>
		<?php echo $form->textField($model,'id'); ?>
		<?php echo $form->error($model,'id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'class_id'); ?>
		<?php echo $form->textField($model,'class_id',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'class_id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'classroom_id'); ?>
		<?php echo $form->textField($model,'classroom_id',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'classroom_id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'teacher1_id'); ?>
		<?php echo $form->textField($model,'teacher1_id',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'teacher1_id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'teacher2_id'); ?>
		<?php echo $form->textField($model,'teacher2_id',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'teacher2_id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'exam_time'); ?>
		<?php echo $form->textField($model,'exam_time',array('size'=>45,'maxlength'=>45)); ?>
		<?php echo $form->error($model,'exam_time'); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? 'Create' : 'Save'); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->