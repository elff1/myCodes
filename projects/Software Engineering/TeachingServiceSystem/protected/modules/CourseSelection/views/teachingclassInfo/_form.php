<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'teachingclass-info-form',
	'enableAjaxValidation'=>false,
)); ?>

	<p class="note">Fields with <span class="required">*</span> are required.</p>

	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'class_id'); ?>
		<?php echo $form->textField($model,'class_id'); ?>
		<?php echo $form->error($model,'class_id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'course_num'); ?>
		<?php echo $form->textField($model,'course_num',array('size'=>9,'maxlength'=>9)); ?>
		<?php echo $form->error($model,'course_num'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'max'); ?>
		<?php echo $form->textField($model,'max',array('size'=>45,'maxlength'=>45)); ?>
		<?php echo $form->error($model,'max'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'term'); ?>
		<?php echo $form->textField($model,'term',array('size'=>45,'maxlength'=>45)); ?>
		<?php echo $form->error($model,'term'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'campus'); ?>
		<?php echo $form->textField($model,'campus',array('size'=>45,'maxlength'=>45)); ?>
		<?php echo $form->error($model,'campus'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'dependence'); ?>
		<?php echo $form->textField($model,'dependence'); ?>
		<?php echo $form->error($model,'dependence'); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? 'Create' : 'Save'); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->