<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'course-sel-sched-form',
	'enableAjaxValidation'=>false,
)); ?>

	<p class="note">Fields with <span class="required">*</span> are required.</p>

	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'stu_id'); ?>
		<?php echo $form->textField($model,'stu_id',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'stu_id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'class_id'); ?>
		<?php echo $form->textField($model,'class_id',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'class_id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'required'); ?>
		<?php echo $form->textField($model,'required',array('size'=>1,'maxlength'=>1)); ?>
		<?php echo $form->error($model,'required'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'repeated'); ?>
		<?php echo $form->textField($model,'repeated',array('size'=>1,'maxlength'=>1)); ?>
		<?php echo $form->error($model,'repeated'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'abandoned'); ?>
		<?php echo $form->textField($model,'abandoned',array('size'=>1,'maxlength'=>1)); ?>
		<?php echo $form->error($model,'abandoned'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'score'); ?>
		<?php echo $form->textField($model,'score'); ?>
		<?php echo $form->error($model,'score'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'year'); ?>
		<?php echo $form->textField($model,'year',array('size'=>9,'maxlength'=>9)); ?>
		<?php echo $form->error($model,'year'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'term'); ?>
		<?php echo $form->textField($model,'term'); ?>
		<?php echo $form->error($model,'term'); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? 'Create' : 'Save'); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->